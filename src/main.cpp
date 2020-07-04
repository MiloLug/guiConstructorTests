#include <iostream>
#include "GUIGL/Components/Container.h"
#include "GUIGL/Elements/Element.h"
#include "GUIGL/Elements/ElementContainer.h"
#include "GUIGL/Elements/Window.h"

#include "GUIGL/Components/Style/StyleStorage.h"

#include <string>
#include <map>
#include <unordered_map>
#include <array>
#include <chrono>

#include <Math.h>

#include <thread>

#include "GUIGL/Components/Event/DataPack.h"

#include "GUIGL/Components/Event/ThreadLoops.h"
#include "GUIGL/Components/Event/Emitter.h"

#include <string>

#include "GUIGL/common.h"

#include <mutex>


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


GUI::Event::defaultListenerFn_t* fc;

void kek() {
	int g = 1;
}

class gg {
public:
	int c = 3;
};

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



	GUI::Event::init();

	
	struct TmpStruct {
		int count;
		std::string id;
	};
	std::mutex m;

	GUI::Event::on("exit", [&m](GUI::Event::DataPack*) {
		m.lock();
		std::cout << "exit!" << std::endl;
		m.unlock();
		GUI::Event::terminate(true);
	});

	GUI::Event::on("tester", [&m](GUI::Event::DataPack* dt) {
		TmpStruct* tmp = &((GUI::Event::DataPackCast<TmpStruct>*)dt)->data;

		for (int i = 0; i < tmp->count; i++) {
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			m.lock();
			std::cout << "test: " << tmp->id << " _ " << i << std::endl;
			m.unlock();
		}
	});

	GUI::Event::emit("tester", new GUI::Event::DataPackCast<TmpStruct>({
		10,
		"first"
	}));

	std::this_thread::sleep_for(std::chrono::milliseconds(6000));

	std::cout << "main thread!" << std::endl;

	GUI::Event::emit("tester", new GUI::Event::DataPackCast<TmpStruct>({
		6,
		"second"
	}));

	std::this_thread::sleep_for(std::chrono::milliseconds(3000));

	GUI::Event::emit("exit");

	GUI::Event::emit("tester", new GUI::Event::DataPackCast<TmpStruct>({
		6,
		"third"
	}));

	GUI::Event::wait();

	std::this_thread::sleep_for(std::chrono::milliseconds(10000));

	std::cout << "main thread!" << std::endl;
	/*std::function<void()> f1 = []() {
		int i = 1;
	};
	std::function<void()> f2 = kek;


	std::cout << GUI::compareFn(f1, f2) << std::endl;
	std::cout << GUI::compareFn(f1, f1) << std::endl;
	std::cout << GUI::compareFn(f2, f2) << std::endl;
	std::cout << GUI::compareFn(std::function<void()>(f2), f2) << std::endl;


	std::map<int, int> dt;

	dt[2] = 3;

	dt[2]++;

	std::cout << dt[2] << std::endl;*/

	//{
	//	using namespace GUI;
	//	using namespace Event;

	//	ThreadLoops::init();
	//	defaultListenerFn_t t = [&t](DataPack* d) {
	//		int tmp = ((DataPackCast<int>*)d)->data;
	//		if (tmp == 3000) {
	//			ThreadLoops::terminate();
	//			return;
	//		}

	//		std::cout << tmp << std::endl;

	//		ThreadLoops::addExecutable(new DataPackCast<int>(tmp+1), t);
	//	};

	//	ThreadLoops::addExecutable(new DataPackCast<int>(22), t);	

	//	ThreadLoops::wait();

	//	/*std::function<void(int)> t = [&t](int d) {
	//		int tmp = d;
	//		if (tmp == 3000) {
	//			ThreadLoops::terminate();
	//			return;
	//		}

	//		std::cout << tmp << std::endl;

	//		t(tmp+1);
	//	};

	//	t(22);*/
	//	
	//}


	//{
	//	using namespace GUI;
	//	using namespace Event;
	//	using namespace std;

	//	unordered_set<int> gg;
	//	gg.insert(3);
	//	gg.insert(2);
	//	gg.insert(1);
	//	gg.insert(10);

	//	class tmp{
	//	public:
	//		~tmp() {
	//			cout << "oh my god!" << endl; //вызовется при удалении
	//		}
	//		int dd = 3;
	//	};
	//	tmp* lol = new tmp;

	//	DataPack* t = new DataPackCast<std::string>("kek");
	//	DataPack* t2 = new DataPackCast<int>(22);
	//	DataPack* t3 = new DataPackCast<float>(22.3);
	//	DataPack* t4 = new DataPackCast<unordered_set<int>*>(&gg); //работает, но там для вывода код некрасивый
	//	DataPack* t5 = new DataPackAutoClean<tmp*>(lol);

	//	std::cout << ((DataPackCast<std::string>*)t)->data << endl;
	//	std::cout << ((DataPackCast<int>*)t2)->data << endl;
	//	std::cout << ((DataPackCast<float>*)t3)->data << endl;
	//	std::cout << ((DataPackCast<tmp*>*)t5)->data->dd << endl;

	//	delete t;
	//	delete t2;
	//	delete t3;
	//	delete t4;
	//	delete t5;
	//}

	

	/*time_t tt = 0;

	for (int i = 0; i < 100; i++) {
		int32_t tmpi = 0;
		auto tp1 = std::chrono::system_clock::now();

		for (int s = 0; s < 1000; s++)
			tmp->width(stateMap);

		auto tp2 = std::chrono::system_clock::now();
		tt += std::chrono::duration_cast<std::chrono::milliseconds>(tp2 - tp1).count();
	}

	tt /= 100;
	std::cout << std::endl << tt;*/


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