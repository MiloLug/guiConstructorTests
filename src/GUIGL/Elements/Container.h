#pragma once
#ifndef __ELEMENTS_CONTAINER

#define __ELEMENTS_CONTAINER

#include "../common.h"
#include <vector>
#include "Element.h"
#include <unordered_set>

namespace GUI {
	namespace Elements {
		class Container
		{
		public:
//base type info =========================
			static const std::type_info* __base_type;
			virtual const std::type_info* __current_type();

//data =========================
			std::unordered_set<Element*> elements;

//constructor =========================
			Container();

//some methods =========================
			virtual Container* linkElement(Element* elem);
			virtual Container* unlinkElement(Element* elem);
			virtual Container* unlinkAll();

			virtual void removeSelf();
			virtual ~Container();
		};
	}
}

#endif