#include "ElementContainer.h"
#include "Window.h"

#include <iostream>
namespace GUI {
	namespace Elements {
		//base type info =========================
		const std::type_info* ElementContainer::__base_type = &typeid(ElementContainer);
		const std::type_info* ElementContainer::__current_type() {
			return &typeid(ElementContainer);
		}
		//attributes =========================

		//data =========================
		inline Window* ElementContainer::parentWindow() {
			return this->_parentWindow;
		}
		inline Element* ElementContainer::parentWindow(Window* w) {
			this->_parentWindow = w;
			std::unordered_set<Element*>::iterator iter = this->elements.begin(),
				end = this->elements.end();
			for (; (iter != end); iter++) {
				(*iter)->parentWindow(w);
			}
			return this;
		}
		//constructor =========================
		ElementContainer::ElementContainer() : Element(), Container() {}

		//some methods =========================
		ElementContainer* ElementContainer::addElement(Element* elem) {
			if (elem->parent() != nullptr) {
				if (elem->parent() == this)
					return this;
				((ElementContainer*)elem->parent())->unlinkElement(elem);
			}
			elem->parent(this)
				->parentWindow(this->parentWindow())
				->__linkContainer(this);
			this->elements.insert(elem);
			return this;
		};
		ElementContainer* ElementContainer::removeElement(Element* elem) {
			if (elem->parent() == this) {
				elem->removeSelf();
			}
			return this;
		};

		inline ElementContainer* ElementContainer::linkElement(Element* elem) {
			return this->addElement(elem);
		};

		ElementContainer* ElementContainer::unlinkElement(Element* elem) {
			if (elem->parent() == this) {
				elem->parent(nullptr)
					->parentWindow(nullptr)
					->__unlinkContainer(this);
				this->elements.erase(elem);
			}
			return this;
		};

		ElementContainer* ElementContainer::unlinkAll() {
			std::unordered_set<Element*>::iterator iter = this->elements.begin(),
				end = this->elements.end();
			for (; (iter != end); iter++) {
				(*iter)->parent(nullptr)
					->parentWindow(nullptr)
					->__unlinkContainer(this);
			}
			this->elements.clear();
			return this;
		};
		ElementContainer* ElementContainer::removeAll() {
			std::unordered_set<Element*>::iterator iter = this->elements.begin();
			Element* tmp;
			while (iter != this->elements.end()) {
				tmp = *iter;
				iter = this->elements.erase(iter);
				tmp->parent(nullptr)
					->parentWindow(nullptr);
				if (tmp->__containersCount() == 0)
					tmp->removeSelf();
				else
					tmp->__unlinkContainer(this);
			}
			return this;
		};

		void ElementContainer::__drawBase(int wwidth, int wheight) {}

		void ElementContainer::removeSelf() {
			this->removeAll()
				->Element::removeSelf();
		}
		ElementContainer::~ElementContainer() {}
	}
}