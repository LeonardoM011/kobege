#pragma once
#include <string>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Input/InputManager.h"
#include "externcode/glfwexterns/GLFWWindowPos.h"

class WindowManager {
public:
	WindowManager();
	~WindowManager();
	int create(int width, int height, const char *title);
	bool closeRequested();
	void swap();
	void pollEvents();
	int getWidth() const { return _width; }
	int getHeight() const { return _height; }
	GLFWwindow* window;
private:
	int _width;
	int _height;
};

