#include "Window.h"
//#include "../Draw.h"
//#include "../Event.h"


namespace GUI {
	class GLFWwindow;
	namespace Elements {
		//base type info =========================
		const std::type_info* Window::__base_type = &typeid(Window);
		const std::type_info* Window::__current_type() {
			return &typeid(Window);
		}
		//attributes =========================

		//data =========================
		inline Window* Window::parentWindow() {
			return this;
		}
		inline Element* Window::parent() {
			return nullptr;
		}
		inline Element* Window::parentWindow(Window* w) {
			return this;
		}
		inline Element* Window::parent(Element* el) {
			return this;
		}
		//constructor =========================
		Window::Window() : ElementContainer() {
			/*this->sysWindow = new SysWindow(100, 100, "");
			this->sysWindow->setUserPointer(this);

			this->sysWindow->framebufferSizeCallback(Window::framebufferSizeCallback);
			this->sysWindow->cursorPosCallback(Window::cursorPosCallback);
			this->sysWindow->cursorEnterCallback(Window::cursorEnterCallback);
			this->sysWindow->closeCallback(Window::closeCallback);
			this->sysWindow->mouseButtonCallback(Window::mouseButtonCallback);*/
		}

		//some methods =========================
		void Window::__drawBase(int wwidth, int wheight) {
			/*if (!this->nativeResizing) {
				glfwSetWindowSize(this->sysWindow->instance, this->style->_width, this->style->_height);
			}
			else
				this->nativeResizing = false;
			glfwSetWindowTitle(this->sysWindow->instance, this->_title.data());
			glClearColor(this->style->_background[0], this->style->_background[1], this->style->_background[2], this->style->_background[3]);
			glClear(GL_COLOR_BUFFER_BIT);*/
		}


		Window* Window::reviewCoordList() {

			return this;
		};
		Window* Window::addToCoordList(int z, int x, int y, int w, int h, Element* elem) {
			std::pair<Window::list_coordMap_t::iterator, bool> tmp = this->coordList.emplace(z, nullptr);

			if (tmp.second) {
				tmp.first->second = new Window::list_coordMap_t;
			}

			tmp = ((Window::list_coordMap_t*)tmp.first->second)->emplace(x, nullptr);
			if (tmp.second) {
				tmp.first->second = new Window::list_coordMap_t;
			}

			tmp = ((Window::list_coordMap_t*)tmp.first->second)->emplace(y, nullptr);
			if (tmp.second) {
				tmp.first->second = new Window::list_coordMap_t;
			}

			tmp = ((Window::list_coordMap_t*)tmp.first->second)->emplace(w, nullptr);
			if (tmp.second) {
				tmp.first->second = new Window::list_coordMap_t;
			}

			tmp = ((Window::list_coordMap_t*)tmp.first->second)->emplace(h, nullptr);
			if (tmp.second) {
				tmp.first->second = new Window::list_elementsSet_t;
			}

			((Window::list_elementsSet_t*)tmp.first->second)->insert(elem);

			return this;
		};

		Window* Window::removeFromCoordList(int z, int x, int y, int w, int h, Element* elem) {
			Window::list_coordMap_t* xList,
				* yList,
				* wList,
				* hList;
			Window::list_elementsSet_t* eList;
			Window::list_coordMap_t::iterator coordIter1, coordIter2, coordIter3, coordIter4, coordIter5;

			coordIter1 = this->coordList.find(z);
			if (coordIter1 != this->coordList.end()) {
				xList = (Window::list_coordMap_t*)coordIter1->second;

				coordIter2 = xList->find(x);
				if (coordIter2 != xList->end()) {
					yList = (Window::list_coordMap_t*)coordIter2->second;

					coordIter3 = yList->find(y);
					if (coordIter3 != yList->end()) {
						wList = (Window::list_coordMap_t*)coordIter3->second;

						coordIter4 = wList->find(w);
						if (coordIter4 != wList->end()) {
							hList = (Window::list_coordMap_t*)coordIter4->second;

							coordIter5 = hList->find(h);
							if (coordIter5 != hList->end()) {
								eList = (Window::list_elementsSet_t*)coordIter5->second;
								eList->erase(elem);
								if (eList->empty()) {
									delete eList;
									hList->erase(coordIter5);
								}
							}
							if (hList->empty()) {
								delete hList;
								wList->erase(coordIter4);
							}
						}
						if (wList->empty()) {
							delete wList;
							yList->erase(coordIter3);
						}
					}
					if (yList->empty()) {
						delete yList;
						xList->erase(coordIter2);
					}
				}
				if (xList->empty()) {
					delete xList;
					this->coordList.erase(coordIter1);
				}
			}

			return this;
		};

		Window* Window::moveInCoordList(int fz, int fx, int fy, int fw, int fh,
			int tz, int tx, int ty, int tw, int th, Element* elem) {

			if (fz == tz && fx == tx && fy == ty && fw == tw && fh == th)
				return this;

			Window::list_coordMap_t* xList,
				* yList,
				* wList,
				* hList;
			Window::list_elementsSet_t* eList;
			Window::list_coordMap_t::iterator coordIter1, coordIter2, coordIter3, coordIter4, coordIter5;

			coordIter1 = this->coordList.find(fz);
			if (coordIter1 != this->coordList.end()) {
				xList = (Window::list_coordMap_t*)coordIter1->second;

				coordIter2 = xList->find(fx);
				if (coordIter2 != xList->end()) {
					yList = (Window::list_coordMap_t*)coordIter2->second;

					coordIter3 = yList->find(fy);
					if (coordIter3 != yList->end()) {
						wList = (Window::list_coordMap_t*)coordIter3->second;

						coordIter4 = wList->find(fw);
						if (coordIter4 != wList->end()) {
							hList = (Window::list_coordMap_t*)coordIter4->second;

							coordIter5 = hList->find(fh);
							if (coordIter5 != hList->end()) {
								eList = (Window::list_elementsSet_t*)coordIter5->second;
								eList->erase(elem);
								if (eList->empty()) {
									delete eList;
									hList->erase(coordIter5);
								}
							}
							if (fw != tw && hList->empty()) {
								delete hList;
								wList->erase(coordIter4);
							}
						}
						if (fy != ty && wList->empty()) {
							delete wList;
							yList->erase(coordIter3);
						}
					}
					if (fx != tx && yList->empty()) {
						delete yList;
						xList->erase(coordIter2);
					}
				}
				if (fz != tz && xList->empty()) {
					delete xList;
					this->coordList.erase(coordIter1);
				}
			}

			this->addToCoordList(tz, tx, ty, tw, th, elem);

			return this;
		};

		Element* Window::findInCoordList(int x, int y) {
			Window::list_coordMap_t* xList,
				* yList,
				* wList,
				* hList;
			list_coordMap_t::reverse_iterator itZ, itX, itY, itW, itH,
				endZ, endX, endY, endW, endH;
			Window::list_elementsSet_t* eList;

			int tmpw, tmph;

			endZ = this->coordList.rend();
			for (itZ = this->coordList.rbegin(); itZ != endZ; ++itZ) {
				xList = (list_coordMap_t*)itZ->second;
				endX = xList->rend();
				for (itX = xList->rbegin(); itX != endX; ++itX) {
					if (itX->first > x)
						continue;
					tmpw = x - itX->first;
					yList = (list_coordMap_t*)itX->second;
					endY = yList->rend();
					for (itY = yList->rbegin(); itY != endY; ++itY) {
						if (itY->first > y)
							continue;
						tmph = y - itY->first;
						wList = (list_coordMap_t*)itY->second;
						endW = wList->rend();
						for (itW = wList->rbegin(); itW != endW && !(itW->first < tmpw); ++itW) {
							hList = (list_coordMap_t*)itW->second;
							endH = hList->rend();
							for (itH = hList->rbegin(); itH != endH && !(itH->first < tmph); ++itH) {
								eList = (list_elementsSet_t*)itH->second;
								if (!eList->empty()) {
									return *eList->begin();
								}
							}
						}
					}
				}
			}
			return nullptr;
		};

		void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
			/*Window* _this = (Window*)glfwGetWindowUserPointer(window);
			Event::baseEvent* tmp = new Event::framebufferSizeEvent(width, height);
			tmp->window = _this->id;
			Event::emit(__EVENT_FRAMEBUFFER_SIZE, tmp);
			Event::execAll();

			_this->nativeResizing = true;
			_this->style->_width = width;
			_this->style->_height = height;
			_this->__redraw = true;

			Draw::draw();*/
		}
		void Window::cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
			/*Window* _this = (Window*)glfwGetWindowUserPointer(window);
			Event::baseEvent* tmp = new Event::mouseMoveEvent(xpos, ypos);
			tmp->window = _this->id;
			tmp->eventId = EVENT_MOUSE_MOVE;
			Event::emit(__EVENT_MOUSE_MOVE, tmp);*/
		}
		void Window::closeCallback(GLFWwindow* window) {
			/*Window* _this = (Window*)glfwGetWindowUserPointer(window);
			Event::baseEvent* tmp = new Event::closeEvent();
			tmp->window = _this->id;
			Event::emit(__EVENT_CLOSE, tmp);*/
		}
		void Window::cursorEnterCallback(GLFWwindow* window, int entered) {
			/*Window* _this = (Window*)glfwGetWindowUserPointer(window);
			Event::baseEvent* tmp;
			if (entered) {
				tmp = new Event::windowMouseEnterEvent();
				tmp->window = _this->id;
				Event::emit(__EVENT_WINDOW_MOUSE_ENTER, tmp);
			}
			else {
				tmp = new Event::windowMouseLeaveEvent();
				tmp->window = _this->id;
				Event::emit(__EVENT_WINDOW_MOUSE_LEAVE, tmp);
			}*/
		};
		void Window::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
			/*Window* _this = (Window*)glfwGetWindowUserPointer(window);
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);

			Event::mouseButtonEvent* tmp = new Event::mouseButtonEvent(xpos,ypos, button);
			tmp->window = _this->id;

			if (action == GLFW_PRESS)
				tmp->eventId = EVENT_MOUSE_DOWN;
			else
				tmp->eventId = EVENT_MOUSE_UP;

			Event::emit(__EVENT_MOUSE_MOVE, tmp);*/
		}

		void Window::removeSelf() {
			this->removeAll();
			delete this;
		}
		Window::~Window() {
			//delete this->sysWindow;
		}
	}
}