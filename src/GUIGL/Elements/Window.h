#pragma once
#ifndef __ELEMENTS_WINDOW

#define __ELEMENTS_WINDOW

#include "../common.h"
#include <string>
#include <functional>

//#include "../GLFW/SysWindow.h"
#include "ElementContainer.h"
#include "Element.h"

#include <map>
#include <unordered_set>

namespace GUI {
	class GLFWwindow;
	namespace Elements {
		class Window : public ElementContainer {
		public:
			typedef std::unordered_set<Element*> list_elementsSet_t;
			typedef std::map<const int, void*> list_coordMap_t;

			//base type info =========================
			static const std::type_info* __base_type;
			virtual const std::type_info* __current_type();
			//attributes =========================

			//data =========================
			bool nativeResizing = false;
			//SysWindow* sysWindow = nullptr;

			list_coordMap_t coordList;

			inline virtual Window* parentWindow();
			inline virtual Element* parent();
			inline virtual Element* parentWindow(Window* w);
			inline virtual Element* parent(Element* el);
			//constructor =========================
			Window();
			Window(const Window& win) = delete;
			Window(const Window* win) = delete;

			//some methods =========================
			virtual void __drawBase(int wwidth, int wheight);

			virtual Window* reviewCoordList();
			virtual Window* addToCoordList(int z, int x, int y, int w, int h, Element* elem);
			virtual Window* removeFromCoordList(int z, int x, int y, int w, int h, Element* elem);
			virtual Window* moveInCoordList(int fz, int fx, int fy, int fw, int fh,
				int tz, int tx, int ty, int tw, int th, Element* elem);
			virtual Element* findInCoordList(int x, int y);

			static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
			static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
			static void cursorEnterCallback(GLFWwindow* window, int entered);
			static void closeCallback(GLFWwindow* window);
			static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

			virtual void removeSelf();
			virtual ~Window();
		};
	}
}

#endif