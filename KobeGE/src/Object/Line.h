#pragma once
#include <GL/glew.h>
#include "Object/Object.h"
#include "Structs/ObjectStruct.h"

// PLEASE DON'T USE THIS YET!!!

class Line {
public:
	Line();
	~Line();
	void init(float x1, float y1, float x2, float y2, float width = 0);
	void draw();
private:
	void upload(VertexStruct vertexData[], int sizeOfVertexData, GLuint indices[], int sizeOfIndices);
	GLuint _vaoID;
	GLuint _vboID;
	GLuint _eboID;
	int vertexCount;
};

