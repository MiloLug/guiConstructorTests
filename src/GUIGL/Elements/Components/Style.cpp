#include "Style.h"

namespace GUI {
	namespace Style {
		//style set
		void StyleSet::removeSelf() {
			delete this;
		}
		StyleSet::~StyleSet() {}

		int StyleSet::width() { //get
			return this->_width;
		};
		StyleSet* StyleSet::width(int t) { //set
			this->_width = t;
			this->_widthSet = true;
			return this;
		};

		int StyleSet::height() { //get
			return this->_height;
		};
		StyleSet* StyleSet::height(int t) { //set
			this->_height = t;
			this->_heightSet = true;
			return this;
		};

		int StyleSet::left() { //get
			return this->_left;
		};
		StyleSet* StyleSet::left(int t) { //set
			this->_left = t;
			this->_leftSet = true;
			return this;
		};

		int StyleSet::top() { //get
			return this->_top;
		};
		StyleSet* StyleSet::top(int t) { //set
			this->_top = t;
			this->_topSet = true;
			return this;
		};

		int StyleSet::zIndex() { //get
			return this->_zIndex;
		};
		StyleSet* StyleSet::zIndex(int t) { //set
			this->_zIndex = t;
			this->_zIndexSet = true;
			return this;
		};


		//state mixer
		void StyleSetStateMixer::removeSelf() {
			delete this;
		}
		StyleSetStateMixer::~StyleSetStateMixer() {}
			int StyleSetStateMixer::width(bool* interactState) { //get
			return (this->sets + (
				interactState[STYLE_press - 1] && (this->sets + STYLE_press)->_widthSet
				? STYLE_press
				: interactState[STYLE_hover - 1] && (this->sets + STYLE_hover)->_widthSet
				? STYLE_hover
				: STYLE_plain
				))->_width;
		};
		bool StyleSetStateMixer::widthSet(bool* interactState) { // get
			return (interactState[STYLE_press - 1] && (this->sets + STYLE_press)->_widthSet)
				|| interactState[STYLE_hover - 1] && (this->sets + STYLE_hover)->_widthSet
				|| this->sets->_widthSet;
		}

		int StyleSetStateMixer::height(bool* interactState) { //get
			return (this->sets + (
				interactState[STYLE_press - 1] && (this->sets + STYLE_press)->_heightSet
				? STYLE_press
				: interactState[STYLE_hover - 1] && (this->sets + STYLE_hover)->_heightSet
				? STYLE_hover
				: STYLE_plain
				))->_height;
		};
		bool StyleSetStateMixer::heightSet(bool* interactState) { // get
			return (interactState[STYLE_press - 1] && (this->sets + STYLE_press)->_heightSet)
				|| interactState[STYLE_hover - 1] && (this->sets + STYLE_hover)->_heightSet
				|| this->sets->_heightSet;
		}

		int StyleSetStateMixer::left(bool* interactState) { //get
			return (this->sets + (
				interactState[STYLE_press - 1] && (this->sets + STYLE_press)->_leftSet
				? STYLE_press
				: interactState[STYLE_hover - 1] && (this->sets + STYLE_hover)->_leftSet
				? STYLE_hover
				: STYLE_plain
				))->_left;
		};
		bool StyleSetStateMixer::leftSet(bool* interactState) { // get
			return (interactState[STYLE_press - 1] && (this->sets + STYLE_press)->_leftSet)
				|| interactState[STYLE_hover - 1] && (this->sets + STYLE_hover)->_leftSet
				|| this->sets->_leftSet;
		}

		int StyleSetStateMixer::top(bool* interactState) { //get
			return (this->sets + (
				interactState[STYLE_press - 1] && (this->sets + STYLE_press)->_topSet
				? STYLE_press
				: interactState[STYLE_hover - 1] && (this->sets + STYLE_hover)->_topSet
				? STYLE_hover
				: STYLE_plain
				))->_top;
		};
		bool StyleSetStateMixer::topSet(bool* interactState) { // get
			return (interactState[STYLE_press - 1] && (this->sets + STYLE_press)->_topSet)
				|| interactState[STYLE_hover - 1] && (this->sets + STYLE_hover)->_topSet
				|| this->sets->_topSet;
		}

		int StyleSetStateMixer::zIndex(bool* interactState) { //get
			return (this->sets + (
				interactState[STYLE_press - 1] && (this->sets + STYLE_press)->_zIndexSet
				? STYLE_press
				: interactState[STYLE_hover - 1] && (this->sets + STYLE_hover)->_zIndexSet
				? STYLE_hover
				: STYLE_plain
				))->_zIndex;
		};
		bool StyleSetStateMixer::zIndexSet(bool* interactState) { // get
			return (interactState[STYLE_press - 1] && (this->sets + STYLE_press)->_zIndexSet)
				|| interactState[STYLE_hover - 1] && (this->sets + STYLE_hover)->_zIndexSet
				|| this->sets->_zIndexSet;
		}


		//aspect mixer
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
		};


		//StylesStorage
		StyleSet* StylesStorage::set(HashId elementId, short int interactState) {
			list_stylesMap_t::const_iterator cur = StylesStorage::styles.find(elementId.data);
			if (cur != StylesStorage::styles.end()) {
				return cur->second->sets + interactState;
			}
			StyleSetStateMixer* t = new StyleSetStateMixer;
			StylesStorage::styles[elementId.data] = t;
			return t->sets + interactState;
		};

		StyleSetStateMixer* StylesStorage::stateMixer(HashId elementId) {
			list_stylesMap_t::const_iterator cur = StylesStorage::styles.find(elementId.data);
			if (cur != StylesStorage::styles.end()) {
				return cur->second;
			}
			StyleSetStateMixer* t = new StyleSetStateMixer;
			StylesStorage::styles[elementId.data] = t;
			return t;
		}

		inline StyleSetStateMixer** StylesStorage::createArray(const std::vector<HashId>& ids) {
			StyleSetStateMixer** tmp = new StyleSetStateMixer * [ids.size()];
			size_t tsize = 0;

			std::vector<HashId>::const_reverse_iterator iter = ids.rbegin(),
				rend = ids.rend();

			list_stylesMap_t::const_iterator cur,
				stylesEnd = StylesStorage::styles.end();

			for (; iter != rend; iter++) {
				cur = StylesStorage::styles.find(iter->data);
				if (cur == stylesEnd) {
					tmp[tsize] = new StyleSetStateMixer;
					StylesStorage::styles[iter->data] = tmp[tsize];
					tsize++;
				}
				else {
					tmp[tsize] = cur->second;
					tsize++;
				}
			}

			return tmp;
		}

		StyleSetAspectMixer* StylesStorage::aspectMixer(const std::vector<HashId>& ids) {
			StyleSetStateMixer** tmp = StylesStorage::createArray(ids);
			return new StyleSetAspectMixer(tmp, tmp + ids.size());
		}
		StylesStorage::list_stylesMap_t StylesStorage::styles;
	}
}