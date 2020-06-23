#pragma once
#define STYLE_plain 0
#define STYLE_hover 1
#define STYLE_press 2
#define STYLE_states_count 3
#define STYLE_states_addCount 2


#define STYLE_class_props\
	int _width = 0;\
	bool _widthSet = false;\
	\
	int _height = 0;\
	bool _heightSet = false;\
	\
	int _left = 0;\
	bool _leftSet = false;\
	\
	int _top = 0;\
	bool _topSet = false;\
	\
	int _zIndex = 0;\
	bool _zIndexSet = false;