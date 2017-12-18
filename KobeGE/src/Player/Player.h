#pragma once
#include "Object/Object.h"
#include "Shaders/ShaderManager.h"
#include "Input/InputManager.h"
#include "GLFW/glfw3.h"

class Player {
public:
	Player();
	~Player();
	void init(glm::vec2 pos, GLdouble width, GLdouble height, ShaderManager shader, int windowWidth, int windowHeight, GLubyte r, GLubyte g, GLubyte b, GLubyte a);
	void draw();
private:
	void handleEvents();
	Object _playerObject;
};

