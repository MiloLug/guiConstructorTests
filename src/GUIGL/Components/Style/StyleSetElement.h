#pragma once
#include "constants.h"
#include "StyleSetAspectMixer.h"
#include "StyleStorage.h"
#include "StyleSet.h"
#include "../../Elements/Element.h"

namespace GUI {
	namespace Style {
		class StyleSetElement : public StyleSet{
		public:
			virtual void removeSelf();
			virtual ~StyleSetElement();

			Elements::Element* el;

			StyleSetElement(StyleSet* set, Elements::Element *el);

			virtual int width(bool* interactState);
			virtual int width();
			virtual StyleSetElement* width(int t);

			virtual int height(bool* interactState);
			virtual int height();
			virtual StyleSetElement* height(int t);

			virtual int left(bool* interactState);
			virtual int left();
			virtual StyleSetElement* left(int t);

			virtual int top(bool* interactState);
			virtual int top();
			virtual StyleSetElement* top(int t);

			virtual int zIndex(bool* interactState);
			virtual int zIndex();
			virtual StyleSetElement* zIndex(int t);

			StyleSetElement* setBase(StyleSet *set);
		};
	}
}

