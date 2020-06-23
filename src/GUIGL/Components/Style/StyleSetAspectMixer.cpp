#include "StyleSetAspectMixer.h"

namespace GUI {
	namespace Style {
		void StyleSetAspectMixer::removeSelf() {
			delete this;
		}
		StyleSetAspectMixer::~StyleSetAspectMixer() {
			if (this->sets != nullptr)
				delete[] this->sets;
		}

		void StyleSetAspectMixer::resetAspects(StyleSetStateMixer** sets, StyleSetStateMixer** setsEnd) {
			if (this->sets != nullptr)
				delete[] this->sets;
			this->sets = sets;
			this->setsEnd = setsEnd;
		}

		StyleSetAspectMixer::StyleSetAspectMixer(StyleSetStateMixer** sets, StyleSetStateMixer** setsEnd) : StyleSet() {
			this->sets = sets;
			this->setsEnd = setsEnd;
		}

		int StyleSetAspectMixer::width(bool* interactState) { //get
			for (StyleSetStateMixer** s = this->sets; s != this->setsEnd; s++) {
				if ((*s)->widthSet(interactState)) {
					return (*s)->width(interactState);
				}
			}
			return this->_width;
		};

		int StyleSetAspectMixer::height(bool* interactState) { //get
			for (StyleSetStateMixer** s = this->sets; s != this->setsEnd; s++) {
				if ((*s)->heightSet(interactState)) {
					return (*s)->height(interactState);
				}
			}
			return this->_height;
		};

		int StyleSetAspectMixer::left(bool* interactState) { //get
			for (StyleSetStateMixer** s = this->sets; s != this->setsEnd; s++) {
				if ((*s)->leftSet(interactState)) {
					return (*s)->left(interactState);
				}
			}
			return this->_left;
		};

		int StyleSetAspectMixer::top(bool* interactState) { //get
			for (StyleSetStateMixer** s = this->sets; s != this->setsEnd; s++) {
				if ((*s)->topSet(interactState)) {
					return (*s)->top(interactState);
				}
			}
			return this->_top;
		};

		int StyleSetAspectMixer::zIndex(bool* interactState) { //get
			for (StyleSetStateMixer** s = this->sets; s != this->setsEnd; s++) {
				if ((*s)->zIndexSet(interactState)) {
					return (*s)->zIndex(interactState);
				}
			}
			return this->_zIndex;
		}
	}
}