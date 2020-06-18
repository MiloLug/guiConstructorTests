#include <iostream>
#include "GUIGL/Elements/Container.h"
#include "GUIGL/Elements/Element.h"
#include "GUIGL/Elements/ElementContainer.h"
#include "GUIGL/Elements/Window.h"

#include <string>
#include <map>
#include <unordered_map>
#include <array>
#include <chrono>

#include <Math.h>

#define STYLE_default 0
#define STYLE_width 1
#define STYLE_height 2
#define STYLE_top 4
#define STYLE_left 5

#define STYLE_plain 0
#define STYLE_hover 1
#define STYLE_press 2
#define STYLE_states_count 3
#define STYLE_states_addCount 2

namespace GUI {

	class StyleSet {
	public:
		virtual void removeSelf() {
			delete this;
		}
		virtual ~StyleSet() {}

		int _width = 0;
		bool _widthSet = false;

		int _height = 0;
		bool _heightSet = false;

		int _left = 0;
		bool _leftSet = false;

		int _top = 0;
		bool _topSet = false;

		int _zIndex = 0;
		bool _zIndexSet = false;

		virtual inline int width() { //get
			return this->_width;
		};
		inline StyleSet* width(int t) { //set
			this->_width = t;
			this->_widthSet = true;
			return this;
		};

		virtual inline int height() { //get
			return this->_height;
		};
		inline StyleSet* height(int t) { //set
			this->_height = t;
			this->_heightSet = true;
			return this;
		};
		
		virtual inline int left() { //get
			return this->_left;
		};
		inline StyleSet* left(int t) { //set
			this->_left = t;
			this->_leftSet = true;
			return this;
		};

		virtual inline int top() { //get
			return this->_top;
		};
		inline StyleSet* top(int t) { //set
			this->_top = t;
			this->_topSet = true;
			return this;
		};

		virtual inline int zIndex() { //get
			return this->_zIndex;
		};
		inline StyleSet* zIndex(int t) { //set
			this->_zIndex = t;
			this->_zIndexSet = true;
			return this;
		};
	};

	class StyleSetStateMixer : public StyleSet {
	public:
		StyleSet sets[STYLE_states_count];

		virtual void removeSelf() {
			delete this;
		}
		virtual ~StyleSetStateMixer() {}

		virtual inline int width(bool *interactState) { //get
			return (this->sets + (
				interactState[STYLE_press - 1] && (this->sets + STYLE_press)->_widthSet
				? STYLE_press
				: interactState[STYLE_hover - 1] && (this->sets + STYLE_hover)->_widthSet
					? STYLE_hover
					: STYLE_plain
			))->_width;
		};
		inline bool widthSet(bool* interactState) { // get
			return (interactState[STYLE_press - 1] && (this->sets + STYLE_press)->_widthSet)
				|| interactState[STYLE_hover - 1] && (this->sets + STYLE_hover)->_widthSet
				|| this->sets->_widthSet;
		}

		virtual inline int height(bool* interactState) { //get
			return (this->sets + (
				interactState[STYLE_press - 1] && (this->sets + STYLE_press)->_heightSet
				? STYLE_press
				: interactState[STYLE_hover - 1] && (this->sets + STYLE_hover)->_heightSet
					? STYLE_hover
					: STYLE_plain
			))->_height;
		};
		inline bool heightSet(bool* interactState) { // get
			return (interactState[STYLE_press - 1] && (this->sets + STYLE_press)->_heightSet)
				|| interactState[STYLE_hover - 1] && (this->sets + STYLE_hover)->_heightSet
				|| this->sets->_heightSet;
		}
		
		virtual inline int left(bool* interactState) { //get
			return (this->sets + (
				interactState[STYLE_press - 1] && (this->sets + STYLE_press)->_leftSet
				? STYLE_press
				: interactState[STYLE_hover - 1] && (this->sets + STYLE_hover)->_leftSet
					? STYLE_hover
					: STYLE_plain
			))->_left;
		};
		inline bool leftSet(bool* interactState) { // get
			return (interactState[STYLE_press - 1] && (this->sets + STYLE_press)->_leftSet)
				|| interactState[STYLE_hover - 1] && (this->sets + STYLE_hover)->_leftSet
				|| this->sets->_leftSet;
		}
		
		virtual inline int top(bool* interactState) { //get
			return (this->sets + (
				interactState[STYLE_press - 1] && (this->sets + STYLE_press)->_topSet
				? STYLE_press
				: interactState[STYLE_hover - 1] && (this->sets + STYLE_hover)->_topSet
					? STYLE_hover
					: STYLE_plain
			))->_top;
		};
		inline bool topSet(bool* interactState) { // get
			return (interactState[STYLE_press - 1] && (this->sets + STYLE_press)->_topSet)
				|| interactState[STYLE_hover - 1] && (this->sets + STYLE_hover)->_topSet
				|| this->sets->_topSet;
		}
		
		virtual inline int zIndex(bool* interactState) { //get
			return (this->sets + (
				interactState[STYLE_press - 1] && (this->sets + STYLE_press)->_zIndexSet
				? STYLE_press
				: interactState[STYLE_hover - 1] && (this->sets + STYLE_hover)->_zIndexSet
					? STYLE_hover
					: STYLE_plain
			))->_zIndex;
		};
		inline bool zIndexSet(bool* interactState) { // get
			return (interactState[STYLE_press - 1] && (this->sets + STYLE_press)->_zIndexSet)
				|| interactState[STYLE_hover - 1] && (this->sets + STYLE_hover)->_zIndexSet
				|| this->sets->_zIndexSet;
		}
	};

	class StyleSetAspectMixer : public StyleSet {
	public:
		StyleSetStateMixer** sets = nullptr;
		StyleSetStateMixer** setsEnd = nullptr;

		virtual void removeSelf() {
			delete this;
		}
		virtual ~StyleSetAspectMixer() {
			if (this->sets != nullptr)
				delete[] this->sets;
		}

		void resetAspects(StyleSetStateMixer** sets, StyleSetStateMixer** setsEnd) {
			if (this->sets != nullptr)
				delete[] this->sets;
			this->sets = sets;
			this->setsEnd = setsEnd;
		}

		StyleSetAspectMixer(StyleSetStateMixer**sets, StyleSetStateMixer** setsEnd) : StyleSet() {
			this->sets = sets;
			this->setsEnd = setsEnd;
		}

		virtual inline int width(bool* interactState) { //get
			for (StyleSetStateMixer** s = this->sets; s != this->setsEnd; s++) {
				if ((*s)->widthSet(interactState)) {
					return (*s)->width(interactState);
				}
			}
			return this->_width;
		};

		virtual inline int height(bool* interactState) { //get
			for (StyleSetStateMixer** s = this->sets; s != this->setsEnd; s++) {
				if ((*s)->heightSet(interactState)) {
					return (*s)->height(interactState);
				}
			}
			return this->_height;
		};

		virtual inline int left(bool* interactState) { //get
			for (StyleSetStateMixer** s = this->sets; s != this->setsEnd; s++) {
				if ((*s)->leftSet(interactState)) {
					return (*s)->left(interactState);
				}
			}
			return this->_left;
		};

		virtual inline int top(bool* interactState) { //get
			for (StyleSetStateMixer** s = this->sets; s != this->setsEnd; s++) {
				if ((*s)->topSet(interactState)) {
					return (*s)->top(interactState);
				}
			}
			return this->_top;
		};

		virtual inline int zIndex(bool* interactState) { //get
			for (StyleSetStateMixer** s = this->sets; s != this->setsEnd; s++) {
				if ((*s)->zIndexSet(interactState)) {
					return (*s)->zIndex(interactState);
				}
			}
			return this->_zIndex;
		};
	};

	class StylesStorage {
	public:
		typedef std::unordered_map<GUI::elemIdNum_t, StyleSetStateMixer*> list_stylesMap_t;
		static list_stylesMap_t styles;
		/*static inline void setStyleSetFields(StyleSet *set, std::unordered_map<int, int> *fields) {
			std::unordered_map<int, int>::const_iterator i = fields->begin(),
				end = fields->end();
			for (i = fields->begin(); i != end; i++) {
				switch (i->first)
				{
					case STYLE_width:
						set->width = i->second;
						break;
				}
			}
		}*/
		static StyleSet* set(HashId elementId, short int interactState = STYLE_plain) {
			list_stylesMap_t::const_iterator cur = StylesStorage::styles.find(elementId.data);
			if (cur != StylesStorage::styles.end()) {
				return cur->second->sets + interactState;
			}
			StyleSetStateMixer* t = new StyleSetStateMixer;
			StylesStorage::styles[elementId.data] = t;
			return t->sets + interactState;
		};

		static StyleSetStateMixer* stateMixer(HashId elementId) {
			list_stylesMap_t::const_iterator cur = StylesStorage::styles.find(elementId.data);
			if (cur != StylesStorage::styles.end()) {
				return cur->second;
			}
			StyleSetStateMixer* t = new StyleSetStateMixer;
			StylesStorage::styles[elementId.data] = t;
			return t;
		}

		static inline StyleSetStateMixer** createArray(const std::vector<HashId>& ids) {
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

		static StyleSetAspectMixer* aspectMixer(const std::vector<HashId> &ids) {
			StyleSetStateMixer** tmp = StylesStorage::createArray(ids);
			return new StyleSetAspectMixer(tmp, tmp + ids.size());
		}
	};
	StylesStorage::list_stylesMap_t StylesStorage::styles;
}


/*
.kek{
	width:100;
	height:300;
	zIndex:2;
}
.kek:hover{
	width:150;
	height:320;
	left:100;
}
.kek:press{  //это у меня для нажимания, а цсс задолбал тем, что там такого нет((((
	width:200;
	height:520;
}

.lol{
	width:70;
	height:1;
}
.lol:hover{
	width:800;
	height:600;
}

/// aspect mix:
.kek.lol {
	width:70;
	height:1;
	zIndex:2;
}

.kek.lol:hover {
	width:800;
	height:600;
	left:100;
}

.kek.lol:press {
	width:200;
	height:520;
}
*/

int main() {
	//GUI::StylesStorage::set(".kek")
	//	->width(100)
	//	->height(300)
	//	->zIndex(2);

	//GUI::StylesStorage::set(".kek", STYLE_hover)
	//	->width(150)
	//	->height(320)
	//	->left(100);

	//GUI::StylesStorage::set(".kek", STYLE_press)
	//	->width(200)
	//	->height(520);

	//GUI::StylesStorage::set(".lol")
	//	->width(70)
	//	->height(1);

	//GUI::StylesStorage::set(".lol", STYLE_hover)
	//	->width(800)
	//	->height(600);

	//GUI::StyleSetAspectMixer* tmp = GUI::StylesStorage::aspectMixer({
	//	".kek",
	//	".lol"
	//});

	//std::cout << "=================== :hover" << std::endl;

	//bool stateMap[2] = {
	//	true, //hover
	//	false  //press
	//};
	//
	//std::cout << "width: " << tmp->width(stateMap) << std::endl;
	//std::cout << "height: " << tmp->height(stateMap) << std::endl;
	//std::cout << "left: " << tmp->left(stateMap) << std::endl;
	//std::cout << "zIndex: " << tmp->zIndex(stateMap) << std::endl;



	GUI::Elements::Window *w = new GUI::Elements::Window;



	time_t tt = 0;

	for (int i = 0; i < 100; i++) {
		int32_t tmpi = 0;
		auto tp1 = std::chrono::system_clock::now();

		GUI::Elements::Element* t = new GUI::Elements::Element;
		w->addElement(t);
		w->moveInCoordList(
			0, 0, 0, 0, 0, 
			1 * i, 2 * i, 3 * i, 1, 1,
			t
		);

		auto tp2 = std::chrono::system_clock::now();
		tt += std::chrono::duration_cast<std::chrono::milliseconds>(tp2 - tp1).count();
	}

	tt /= 100;
	std::cout << std::endl << tt;

	std::cout << std::endl << w->elements.size();
	
	tt = 0;
	for (int i = 0; i < 100; i++) {
		int32_t tmpi = 0;
		auto tp1 = std::chrono::system_clock::now();

		for (; tmpi < 1000; tmpi++)
			w->findInCoordList(0, 1);

		auto tp2 = std::chrono::system_clock::now();

		tt += std::chrono::duration_cast<std::chrono::milliseconds>(tp2 - tp1).count();
	}

	std::cout << std::endl << (float)tt/100000.;
	

	//GUI::StyleSetStateMixer* tmp = GUI::StylesStorage::stateMixer(".kek");


	//std::cout << "=================== :hover:press" << std::endl;

	//bool stateMap[2] = {
	//	true, //hover
	//	true  //press
	//};
	//
	//std::cout << "width: " << tmp->width(stateMap) << std::endl;
	//std::cout << "height: " << tmp->height(stateMap) << std::endl;
	//std::cout << "left: " << tmp->left(stateMap) << std::endl;
	//std::cout << "zIndex: " << tmp->zIndex(stateMap) << std::endl;


	//std::cout << "=================== :hover" << std::endl;

	//stateMap[0] = true;
	//stateMap[1] = false;

	//std::cout << "width: " << tmp->width(stateMap) << std::endl;
	//std::cout << "height: " << tmp->height(stateMap) << std::endl;
	//std::cout << "left: " << tmp->left(stateMap) << std::endl;
	//std::cout << "zIndex: " << tmp->zIndex(stateMap) << std::endl;


	//std::cout << "=================== plain state" << std::endl;

	//stateMap[0] = false;
	//stateMap[1] = false;

	//std::cout << "width: " << tmp->width(stateMap) << std::endl;
	//std::cout << "height: " << tmp->height(stateMap) << std::endl;
	//std::cout << "left: " << tmp->left(stateMap) << std::endl;
	//std::cout << "zIndex: " << tmp->zIndex(stateMap) << std::endl;
	
	return 0;
}