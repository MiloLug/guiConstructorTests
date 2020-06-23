#pragma once
#include "constants.h"

namespace GUI {
	namespace Style {
		class StyleSet {
		public:
			virtual void removeSelf();
			virtual ~StyleSet();

			STYLE_class_props

			virtual  int width();
			virtual StyleSet* width(int t);

			virtual  int height();
			virtual StyleSet* height(int t);

			virtual  int left();
			virtual StyleSet* left(int t);

			virtual  int top();
			virtual StyleSet* top(int t);

			virtual  int zIndex();
			virtual StyleSet* zIndex(int t);
		};
	}
}
