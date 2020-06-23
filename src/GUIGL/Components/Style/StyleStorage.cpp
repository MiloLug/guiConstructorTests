#include "StyleStorage.h"
namespace GUI {
	namespace Style {
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