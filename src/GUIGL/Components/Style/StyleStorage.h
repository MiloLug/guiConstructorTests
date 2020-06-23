#pragma once
#include <unordered_map>
#include "../../common.h"
#include "StyleSet.h"
#include "StyleSetStateMixer.h"
#include "StyleSetAspectMixer.h"
#include "constants.h"

namespace GUI {
	namespace Style {
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
