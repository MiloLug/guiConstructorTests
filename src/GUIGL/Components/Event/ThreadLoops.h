#pragma once
#include <thread>
#include <stack>
#include <functional>
#include "DataPack.h"
#include <mutex>

namespace GUI {
	namespace Event {
		typedef std::function<void(DataPack*)> defaultListenerFn_t;

		class ThreadLoops
		{
		public:
			typedef std::pair<DataPack*, std::stack<defaultListenerFn_t>> fnPair_t;
			
			static std::mutex m;
			static std::stack<fnPair_t*> fnstack;
			static std::stack<std::thread*> threads;
			static bool stop;

			static void executor();

			static bool getExecutable(DataPack*& data, defaultListenerFn_t& fn);

			static void addExecutable(DataPack* data, const defaultListenerFn_t& fn);

			static void addExecutable(DataPack* data, std::stack<defaultListenerFn_t>& fns);

			static void init(size_t maxThreadsNumber = 2);

			static void wait();

			static void terminate();
		};
	}
}

