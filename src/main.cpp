#include <iostream>
#include "GUIGL/Elements/Container.h"
#include "GUIGL/Elements/Element.h"
#include "GUIGL/Elements/ElementContainer.h"
#include "GUIGL/Elements/Window.h"

#include "GUIGL/Style.h"

#include <string>
#include <map>
#include <unordered_map>
#include <array>
#include <chrono>

#include <Math.h>


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
	GUI::Style::StylesStorage::set(".kek")
		->width(100)
		->height(300)
		->zIndex(2);

	GUI::Style::StylesStorage::set(".kek", STYLE_hover)
		->width(150)
		->height(320)
		->left(100);

	GUI::Style::StylesStorage::set(".kek", STYLE_press)
		->width(200)
		->height(520);

	GUI::Style::StylesStorage::set(".lol")
		->width(70)
		->height(1);

	GUI::Style::StylesStorage::set(".lol", STYLE_hover)
		->width(800)
		->height(600);

	GUI::Style::StyleSetAspectMixer* tmp = GUI::Style::StylesStorage::aspectMixer({
		".kek",
		".lol"
	});

	std::cout << "=================== :hover" << std::endl;

	bool stateMap[2] = {
		true, //hover
		false  //press
	};
	
	std::cout << "width: " << tmp->width(stateMap) << std::endl;
	std::cout << "height: " << tmp->height(stateMap) << std::endl;
	std::cout << "left: " << tmp->left(stateMap) << std::endl;
	std::cout << "zIndex: " << tmp->zIndex(stateMap) << std::endl;



	/*GUI::Elements::Window *w = new GUI::Elements::Window;



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

	std::cout << std::endl << (float)tt/100000.;*/
	

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