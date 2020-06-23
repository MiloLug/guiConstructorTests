#include "StyleSet.h"
#include "constants.h"

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
	}
}