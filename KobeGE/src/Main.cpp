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
#include "Object/Camera.h"
#include "Player/Player.h"

int main(int argc, char** argv) {
	if (InitManager::initGlfw()) return PrintError::PrintLn(0, "Glfw failed to init");
	WindowManager window;
	if (window.create(720, 480, "KobeGE")) return PrintError::PrintLn(1, "Window failed to create");
	InitManager::setViewport(window.getWidth(), window.getHeight());
	if (InitManager::initGlew()) return PrintError::PrintLn(2, "Glew failed to init");
	
	std::cout << "OPENGL Version: " << glGetString(GL_VERSION) << std::endl;

	ShaderManager textureShader;
	textureShader.compileShaders("res/shaders/ObjectTextureShader.vert", "res/shaders/ObjectTextureShader.frag");
	textureShader.linkShaders();

	ShaderManager colorShader;
	colorShader.compileShaders("res/shaders/ObjectColorShader.vert", "res/shaders/ObjectColorShader.frag");
	colorShader.linkShaders();

	Camera camera;
	camera.addShader(textureShader);
	camera.addShader(colorShader);

	Player player;
	player.init(glm::vec2(-0.9f, 0.0f), 0.02f, 0.4f, colorShader, window.getWidth(), window.getHeight(), 255, 255, 255, 255);
	
	Object line1;
	line1.init(glm::vec2(0.0f, -0.8), 0.04f, 0.4f, colorShader, window.getWidth(), window.getHeight(), 255, 255, 255, 255);

	glfwSetKeyCallback(window.window, InputManager::key_callback);

	while (window.closeRequested())
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		player.draw();
		line1.draw();

		window.swap();
		window.pollEvents();
	}
	glfwTerminate();
	return 0;
}
