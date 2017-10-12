#pragma once
#include <GL/glew.h>
#include <cstddef>
#include <iostream>
#include "../Structs/ObjectStruct.h"
#include "../Structs/VertexStruct.h"
#include "../Shaders/ShaderManager.h"

class Object {
public:
	Object();
	~Object();
	void init(float x, float y, float width, float height);
	void draw();
private:
	ObjectStruct objInfo;
	ShaderManager shader;
	GLuint _vboID;
	float _tempTime;
};

