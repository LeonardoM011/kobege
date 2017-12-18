#pragma once
#include "Object/Object.h"
#include "Shaders/ShaderManager.h"
#include "Input/InputManager.h"
#include "GLFW/glfw3.h"

class Enemy {
public:
	Enemy();
	~Enemy();
	void init(glm::vec2 pos, GLdouble width, GLdouble height, int windowWidth, int windowHeight, GLubyte r, GLubyte g, GLubyte b, GLubyte a);
	void draw();
private:
	void handleEvents();
	Object _object;
};

