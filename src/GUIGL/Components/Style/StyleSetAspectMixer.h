#pragma once
#include "StyleSet.h"
#include "StyleSetStateMixer.h"

namespace GUI {
	namespace Style {
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
	}
}