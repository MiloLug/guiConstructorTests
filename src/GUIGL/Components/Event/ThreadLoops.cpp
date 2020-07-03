#include "ThreadLoops.h"

namespace GUI {
	namespace Event {
	
		std::mutex ThreadLoops::m;
		std::stack<ThreadLoops::fnPair_t*> ThreadLoops::fnstack;
		std::stack<std::thread*> ThreadLoops::threads;
		bool ThreadLoops::stop = false;

		void ThreadLoops::executor() {
			DataPack* tmpData;
			defaultListenerFn_t tmpFn;
			while (true) {
				if (ThreadLoops::getExecutable(tmpData, tmpFn)) {
					tmpFn(tmpData);
					if (tmpData != nullptr)
						delete tmpData;
				}
				if (ThreadLoops::stop)
					return;
			}
		}

		bool ThreadLoops::getExecutable(DataPack*& data, defaultListenerFn_t& fn) {
			std::lock_guard<std::mutex> guard(ThreadLoops::m);
			if (ThreadLoops::fnstack.empty()) {
				return false;
			}
			else {
				fnPair_t* tmp = ThreadLoops::fnstack.top();

				data = tmp->first == nullptr ? nullptr : tmp->first->copy();
				fn = tmp->second.top();
				tmp->second.pop();

				if (tmp->second.empty()) {
					if (tmp->first != nullptr)
						delete tmp->first;
					delete tmp;
					ThreadLoops::fnstack.pop();
				}

				return true;
			}
		}

		void ThreadLoops::addExecutable(DataPack* data, const defaultListenerFn_t& fn) {
			std::lock_guard<std::mutex> guard(ThreadLoops::m);
			ThreadLoops::fnstack.push(new fnPair_t({
					data,
					std::stack<defaultListenerFn_t>({fn})
				}));
		}

		void ThreadLoops::addExecutable(DataPack* data, std::stack<defaultListenerFn_t>& fns) {
			std::lock_guard<std::mutex> guard(ThreadLoops::m);
			ThreadLoops::fnstack.push(new fnPair_t({
					data,
					fns
				}));
		}

		void ThreadLoops::init(size_t maxThreadsNumber) {
			size_t proc_count = std::thread::hardware_concurrency();
			for (size_t i = 0; i < proc_count && i < maxThreadsNumber; i++) {
				ThreadLoops::threads.push(new std::thread(ThreadLoops::executor));
			}
		}

		void ThreadLoops::wait() {
			size_t threadsNumber = ThreadLoops::threads.size();
			for (size_t i = 0; i < threadsNumber; i++) {
				std::thread* t = ThreadLoops::threads.top();
				t->join();
				delete t;
				ThreadLoops::threads.pop();
			}
		}

		void ThreadLoops::terminate() {
			ThreadLoops::stop = true;
		}
	
	}
}