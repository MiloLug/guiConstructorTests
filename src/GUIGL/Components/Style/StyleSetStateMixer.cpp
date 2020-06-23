#include "StyleSetStateMixer.h"
namespace GUI {
	namespace Style {
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
	}
}