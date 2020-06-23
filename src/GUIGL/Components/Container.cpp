#include "Container.h"

namespace GUI {
	//base type info =========================
	const std::type_info* Container::__base_type = &typeid(Container);
	const std::type_info* Container::__current_type() {
		return &typeid(Container);
	}
	//data =========================

	//constructor =========================
	Container::Container() {

	}

	//some methods =========================
	Container* Container::linkElement(Elements::Element* elem) {
		elem->__linkContainer(this);
		this->elements.insert(elem);
		return this;
	}

	Container* Container::unlinkElement(Elements::Element* elem) {
		this->elements.erase(elem);
		elem->__unlinkContainer(this);
		return this;
	}

	Container* Container::unlinkAll() {
		std::unordered_set<Elements::Element*>::iterator iter = this->elements.begin(),
			end = this->elements.end();
		for (; (iter != end); iter++) {
			(*iter)->__unlinkContainer(this);
		}
		this->elements.clear();
		return this;
	}

	void Container::removeSelf() {
		this->unlinkAll();
		delete this;
	}
	Container::~Container() {}
}