#include "WindowManager.h"

WindowManager::WindowManager() :
	_window(nullptr),
	_width(0),
	_height(0)
{
	
}

WindowManager::~WindowManager() {
	
}

int WindowManager::create(int width, int height, const char *title) {
	_width = width;
	_height = height;
	_window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!_window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(_window);
	return 0;
}

bool WindowManager::closeRequested() {
	return !glfwWindowShouldClose(_window);
}

void WindowManager::swap() {
	glfwSwapBuffers(_window);
}

void WindowManager::pollEvents() {
	glfwPollEvents();
}

void WindowManager::processInput() {
	InputManager::processInput(_window);
}
