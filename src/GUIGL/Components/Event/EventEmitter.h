#pragma once
#include <unordered_map>
#include <vector>
#include <map>
#include "../../common.h"
#include <functional>
#include "DataPack.h"
#include "ThreadLoops.h"
#include <mutex>

namespace GUI {
	namespace Event {
		typedef std::unordered_map<elemIdNum_t, std::vector<defaultListenerFn_t*>> mainListenersMap_t;
		class EventEmitter {
		private:
			std::mutex m;
			mainListenersMap_t listeners;
		public:
			EventEmitter* on(HashId id, const defaultListenerFn_t& fn, defaultListenerFn_t*& listenerPtr) {
				this->m.lock();
				std::vector<defaultListenerFn_t*>* tmp = &this->listeners[id.data];
				tmp->push_back(new defaultListenerFn_t(fn));
				listenerPtr = tmp->operator[](tmp->size()-1);
				this->m.unlock();
				return this;
			}
			EventEmitter* on(HashId id, const defaultListenerFn_t& fn) {
				this->m.lock();
				this->listeners[id.data].push_back(new defaultListenerFn_t(fn));
				this->m.unlock();
				return this;
			}

			EventEmitter* off(HashId id, const defaultListenerFn_t& fn) {
				this->m.lock();
				std::vector<defaultListenerFn_t*>* tmp = &this->listeners[id.data];
				if (!tmp->empty()) {
					std::vector<defaultListenerFn_t*>::iterator cur = tmp->begin(),
						end = tmp->end();
					bool samePointers = false;
					while(cur != end) {
						if (compareFn(fn, **cur)) {
							samePointers = *cur == &fn;
							delete (*cur);
							cur = tmp->erase(cur);
							end = tmp->end();
							if (samePointers)
								break;
						}
						else {
							++cur;
						}
					}
					if (tmp->empty()) {
						this->listeners.erase(id.data);
					}
				}
				this->m.unlock();
				return this;
			}

			EventEmitter* emit(HashId id, DataPack* data = nullptr) {
				this->m.lock();
				std::vector<defaultListenerFn_t*>* tmp = &this->listeners[id.data];
				if (!tmp->empty()) {
					ThreadLoops::addExecutable(data, *tmp);
				}
				this->m.unlock();
				return this;
			}
		};
		extern EventEmitter root;
		inline void init(size_t maxThreadsNumber = 2) {
			ThreadLoops::init(maxThreadsNumber);
		};
		inline void wait() {
			ThreadLoops::wait();
		};
		inline void terminate() {
			ThreadLoops::terminate();
		};
		inline EventEmitter* on(HashId id, const defaultListenerFn_t& fn, defaultListenerFn_t*& listenerPtr) {
			return root.on(id, fn, listenerPtr);
		};
		inline EventEmitter* on(HashId id, const defaultListenerFn_t& fn) {
			return root.on(id, fn);
		};
		inline EventEmitter* off(HashId id, const defaultListenerFn_t& fn) {
			return root.off(id, fn);
		};
		inline EventEmitter* emit(HashId id, DataPack* data = nullptr) {
			return root.emit(id, data);
		};
	}
}

