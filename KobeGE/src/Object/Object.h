#pragma once
#include <GL/glew.h>
#include <cstddef>
#include <iostream>
#include "Structs/ObjectStruct.h"
#include "Structs/VertexStruct.h"

class Object {
public:
	Object();
	~Object();
	void init(float x, float y, float width, float height);
	void draw();
private:
	ObjectStruct objInfo;
	GLuint _vboID;
	GLuint _vaoID;
	GLuint _eboID;
	float _tempTime;
};

