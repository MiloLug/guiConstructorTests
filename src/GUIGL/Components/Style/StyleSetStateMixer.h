#pragma once
#include "StyleSet.h"
#include "constants.h"

namespace GUI {
	namespace Style {
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
	}
}
