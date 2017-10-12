#include "InitManager.h"

int InitManager::initGlfw() {
	if(!glfwInit()) return -1;
	return 0;
}

int InitManager::initGlew() {
	if(glewInit() != GLEW_OK) return -1;
	return 0;
}

void InitManager::setViewport(int windowWidth, int windowHeight) {
	glViewport(0, 0, windowWidth, windowHeight);
}

