#pragma once
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Input/InputManager.h"

class WindowManager {
public:
	WindowManager();
	~WindowManager();
	int create(int width, int height, const char *title);
	bool closeRequested();
	void swap();
	void pollEvents();
	void processInput();
	int getWidth() const { return _width; }
	int getHeight() const { return _height; }
private:
	GLFWwindow* _window;
	int _width;
	int _height;
};

