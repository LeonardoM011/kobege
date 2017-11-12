#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Window/WindowManager.h"

class InitManager {
public:
	static int initGlfw() {
		if (!glfwInit()) return -1;
		return 0;
	}
	static int initGlew() {
		if (glewInit() != GLEW_OK) return -1;
		return 0;
	}
	static void setViewport(int windowWidth, int windowHeight) {
		glViewport(0, 0, windowWidth, windowHeight);
	}
};

