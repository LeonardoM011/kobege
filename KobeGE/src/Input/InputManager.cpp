#include "InputManager.h"
bool InputManager::keydown[350] = { false };

void InputManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	if (action == GLFW_PRESS) {
		keydown[key] = true;
	}
	if (action == GLFW_RELEASE) {
		keydown[key] = false;
	}
}
