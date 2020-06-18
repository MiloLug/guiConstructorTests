#pragma once
#include <unordered_map>
#include "common.h"

#define STYLE_plain 0
#define STYLE_hover 1
#define STYLE_press 2
#define STYLE_states_count 3
#define STYLE_states_addCount 2

namespace GUI {
	namespace Style {
		class StyleSet {
		public:
			virtual void removeSelf();
			virtual ~StyleSet();

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

			virtual  int width();
			 StyleSet* width(int t);

			virtual  int height();
			 StyleSet* height(int t);

			virtual  int left();
			 StyleSet* left(int t);

			virtual  int top();
			 StyleSet* top(int t);

			virtual  int zIndex();
			 StyleSet* zIndex(int t);
		};

		class StyleSetStateMixer : public StyleSet {
		public:
			StyleSet sets[STYLE_states_count];

			virtual void removeSelf();
			virtual ~StyleSetStateMixer();

			virtual  int width(bool* interactState);
			 bool widthSet(bool* interactState);

			virtual  int height(bool* interactState);
			 bool heightSet(bool* interactState);

			virtual  int left(bool* interactState);
			 bool leftSet(bool* interactState);

			virtual  int top(bool* interactState);
			 bool topSet(bool* interactState);

			virtual  int zIndex(bool* interactState);
			 bool zIndexSet(bool* interactState);
		};

		class StyleSetAspectMixer : public StyleSet {
		public:
			StyleSetStateMixer** sets = nullptr;
			StyleSetStateMixer** setsEnd = nullptr;

			virtual void removeSelf();
			virtual ~StyleSetAspectMixer();

			void resetAspects(StyleSetStateMixer** sets, StyleSetStateMixer** setsEnd);

			StyleSetAspectMixer(StyleSetStateMixer** sets, StyleSetStateMixer** setsEnd);

			virtual int width(bool* interactState);

			virtual int height(bool* interactState);

			virtual int left(bool* interactState);

			virtual int top(bool* interactState);

			virtual int zIndex(bool* interactState);
		};

		class StylesStorage {
		public:
			typedef std::unordered_map<GUI::elemIdNum_t, StyleSetStateMixer*> list_stylesMap_t;
			static list_stylesMap_t styles;
			/*static  void setStyleSetFields(StyleSet *set, std::unordered_map<int, int> *fields) {
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
			static StyleSet* set(HashId elementId, short int interactState = STYLE_plain);

			static StyleSetStateMixer* stateMixer(HashId elementId);

			static inline StyleSetStateMixer** createArray(const std::vector<HashId>& ids);

			static StyleSetAspectMixer* aspectMixer(const std::vector<HashId>& ids);
		};
	}
}

