#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

class InputManager {
public:
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static bool keydown[350];
};

