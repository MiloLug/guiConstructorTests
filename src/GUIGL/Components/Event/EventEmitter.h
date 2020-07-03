#pragma once
#include <unordered_map>
#include <map>
#include "../../common.h"
#include <functional>
#include "DataPack.h"
#include "ThreadLoops.h"

namespace GUI {
	namespace Event {
		typedef std::map<elemIdNum_t, defaultListenerFn_t*> mainEmittersMap_t;
		class EventEmitter {

		};
		extern EventEmitter root;
	}
}

