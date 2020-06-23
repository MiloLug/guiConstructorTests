#pragma once

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
	}
}
