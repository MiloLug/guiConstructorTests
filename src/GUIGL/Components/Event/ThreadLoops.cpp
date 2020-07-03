#include "ThreadLoops.h"
#include <iostream>
namespace GUI {
	namespace Event {
	
		std::mutex ThreadLoops::m;
		std::stack<ThreadLoops::fnPair_t*> ThreadLoops::fnstack;
		std::stack<std::thread*> ThreadLoops::threads;
		std::vector<std::mutex*> ThreadLoops::lockers;
		bool ThreadLoops::stop = false;
		std::condition_variable ThreadLoops::cv;
		

		void ThreadLoops::executor(int id) {
			DataPack* tmpData;
			defaultListenerFn_t tmpFn;
			while (!ThreadLoops::stop) {
				if (ThreadLoops::getExecutable(tmpData, tmpFn)) {
					tmpFn(tmpData);
					if (tmpData != nullptr)
						delete tmpData;
				}
				else {
					std::unique_lock<std::mutex> lck(*ThreadLoops::lockers[id]);
					ThreadLoops::cv.wait(lck, ThreadLoops::canContinue);
				}
			}
		}

		inline bool ThreadLoops::canContinue() {
			return ThreadLoops::fnstack.size() > 0 || ThreadLoops::stop;
		}

		bool ThreadLoops::getExecutable(DataPack*& data, defaultListenerFn_t& fn) {
			std::unique_lock<std::mutex> ul(ThreadLoops::m);
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
			ThreadLoops::cv.notify_all();
		}

		void ThreadLoops::addExecutable(DataPack* data, std::stack<defaultListenerFn_t>& fns) {
			std::lock_guard<std::mutex> guard(ThreadLoops::m);
			ThreadLoops::fnstack.push(new fnPair_t({
					data,
					fns
				}));
			ThreadLoops::cv.notify_all();
		}

		void ThreadLoops::addExecutable(DataPack* data, std::vector<defaultListenerFn_t>& fns) {
			std::lock_guard<std::mutex> guard(ThreadLoops::m);
			ThreadLoops::fnstack.push(new fnPair_t({
					data,
					std::stack<defaultListenerFn_t>(std::deque<defaultListenerFn_t>(fns.begin(), fns.end()))
				}));
			ThreadLoops::cv.notify_all();
		}

		void ThreadLoops::addExecutable(DataPack* data, std::vector<defaultListenerFn_t*>& fns) {
			std::lock_guard<std::mutex> guard(ThreadLoops::m);

			fnPair_t *tmpPair = new fnPair_t({
				data,
				{}
			});

			std::vector<defaultListenerFn_t*>::iterator cur = fns.begin(),
				end = fns.end();
			for (; cur != end; cur++) {
				tmpPair->second.push(**cur);
			}
			ThreadLoops::fnstack.push(tmpPair);
			ThreadLoops::cv.notify_all();
		}

		void ThreadLoops::init(size_t maxThreadsNumber) {
			size_t proc_count = std::thread::hardware_concurrency();
			for (size_t i = 0; i < proc_count && i < maxThreadsNumber; i++) {
				ThreadLoops::threads.push(new std::thread(ThreadLoops::executor, i));
				ThreadLoops::lockers.push_back(new std::mutex);
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
			std::vector<std::mutex*>::iterator cur = ThreadLoops::lockers.begin(),
				end = ThreadLoops::lockers.end();
			for (; cur != end; cur++) {
				delete *cur;
			}
			ThreadLoops::lockers.clear();
		}

		void ThreadLoops::terminate() {
			ThreadLoops::stop = true;
			ThreadLoops::cv.notify_all();
		}
	
	}
}