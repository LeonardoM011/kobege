#pragma once
#include <Windows.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "System/InitManager.h"
#include "Window/WindowManager.h"
#include "ErrorChecking/PrintError.h"
#include "Object/Object.h"
#include "Shaders/ShaderManager.h"
#include "Object/Line.h"

int main(void)
{
	if (InitManager::initGlfw()) return PrintError::PrintLn(0, "Glfw failed to init");
	WindowManager window;
	if (window.create(720, 480, "KobeGE")) return PrintError::PrintLn(1, "Window failed to create");
	InitManager::setViewport(window.getWidth(), window.getHeight());
	if (InitManager::initGlew()) return PrintError::PrintLn(2, "Glew failed to init");
	
	std::cout << "OPENGL Version: " << glGetString(GL_VERSION) << std::endl;

	Object player1;
	player1.init(ObjectStruct{ -0.9f, -0.2f, 0.02f, 0.4f });
	
	Object player2;
	player2.init(ObjectStruct{ 0.9f, -0.2f, 0.02f, 0.4f });

	ShaderManager shader;
	shader.compileShaders("res/shaders/objectColor.vert", "res/shaders/objectColor.frag");
	shader.linkShaders();

	while (window.closeRequested())
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		shader.startUsing();
		player1.draw();
		player2.draw();
		shader.stopUsing();

		window.processInput();
		window.swap();
		window.pollEvents();
	}
	glfwTerminate();
	return 0;
}
