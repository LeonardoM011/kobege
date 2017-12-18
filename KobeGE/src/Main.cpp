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
#include "NPC/Enemy.h"

int main(int argc, char** argv) {
	if (InitManager::initGlfw()) return PrintError::PrintLn(0, "Glfw failed to init");
	WindowManager window;
	if (window.create(720, 480, "KobeGE")) return PrintError::PrintLn(1, "Window failed to create");
	InitManager::setViewport(window.getWidth(), window.getHeight());
	if (InitManager::initGlew()) return PrintError::PrintLn(2, "Glew failed to init");
	
	std::cout << "OPENGL Version: " << glGetString(GL_VERSION) << std::endl;

	Player player;
	player.init(glm::vec2(-0.9f, 0.0f), 0.02f, 0.4f, window.getWidth(), window.getHeight(), 255, 255, 255, 255);
	
	Enemy enemy;
	enemy.init(glm::vec2(0.9f, 0.0f), 0.02f, 0.4f, window.getWidth(), window.getHeight(), 255, 255, 255, 255);

	Object line[20];
	for (int i = 0; i < 20; i++) {
		line[i].init(glm::vec2(0.0f, -0.95f + 0.1f * i), 0.02f, 0.06f, window.getWidth(), window.getHeight(), 255, 255, 255, 255);
	}
	/*line[0].init(glm::vec2(0.0f, -0.75), 0.02f, 0.4f, window.getWidth(), window.getHeight(), 255, 255, 255, 255);
	line[1].init(glm::vec2(0.0f, -0.25), 0.02f, 0.4f, window.getWidth(), window.getHeight(), 255, 255, 255, 255);
	line[2].init(glm::vec2(0.0f, 0.25), 0.02f, 0.4f, window.getWidth(), window.getHeight(), 255, 255, 255, 255);
	line[3].init(glm::vec2(0.0f, 0.75), 0.02f, 0.4f, window.getWidth(), window.getHeight(), 255, 255, 255, 255);*/

	glfwSetKeyCallback(window.window, InputManager::key_callback);

	while (window.closeRequested())
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		player.draw();
		enemy.draw();
		for (int i = 0; i < 20; i++) {
			line[i].draw();
		}

		window.swap();
		window.pollEvents();
	}
	glfwTerminate();
	return 0;
}
