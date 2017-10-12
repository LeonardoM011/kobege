#pragma once
#include <GL/glew.h>
#include <cstddef>
#include "../Structs/ObjectStruct.h"
#include "../Structs/Vertex.h"
#include "../Shaders/ShaderManager.h"

class Object {
public:
	Object(float x, float y, float width, float height);
	~Object();
	void draw();
private:
	ObjectStruct objInfo;
	ShaderManager shader;
	GLuint _vboID;
	float _tempTime;
};

