#include "InitManager.h"

int InitManager::initGlfw() {
	if(!glfwInit()) return -1;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	return 0;
}

int InitManager::initGlew() {
	if(glewInit() != GLEW_OK) return -1;
	return 0;
}

void InitManager::setViewport(int windowWidth, int windowHeight) {
	glViewport(0, 0, windowWidth, windowHeight);
}

