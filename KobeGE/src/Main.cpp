#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "System/InitManager.h"
#include "Window/WindowManager.h"
#include "ErrorChecking/PrintError.h"
#include "Object/Object.h"

int main(void)
{
	if (InitManager::initGlfw()) return PrintError::PrintLn(0, "Glfw failed to init");
	WindowManager window;
	if (window.create(1280, 800, "KobeGE")) return PrintError::PrintLn(1, "Window failed to create");
	if (InitManager::initGlew()) return PrintError::PrintLn(2, "Glew failed to init");
	InitManager::setViewport(window.getWidth(), window.getHeight());
	std::cout << "OPENGL Version: " << glGetString(GL_VERSION) << std::endl;

	Object box(0.0f, 0.0f, 1.0f, 1.0f);

	while (window.closeRequested())
	{
		glClearColor(0.5f, 0.2f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		box.draw();
		
		window.processInput();
		window.swap();
		window.pollEvents();
	}
	glfwTerminate();
	return 0;
}