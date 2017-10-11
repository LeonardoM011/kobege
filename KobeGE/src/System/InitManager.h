#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Window/WindowManager.h"

class InitManager {
public:
	static int initGlfw();
	static int initGlew();
	static void setViewport(int windowWidth, int windowHeight);
};

