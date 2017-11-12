#include "Line.h"

Line::Line() {

}

Line::~Line() {

}

void Line::init(float x1, float y1, float x2, float y2, float width) {
	if (_vaoID == 0)
		glGenVertexArrays(1, &_vaoID);
	if (_vboID == 0)
		glGenBuffers(1, &_vboID);
	if (_eboID == 0)
		glGenBuffers(1, &_eboID);

	VertexStruct vertexData[2];

	vertexData[0].position.x = x1;
	vertexData[0].position.y = y1;

	vertexData[1].position.x = x2;
	vertexData[1].position.y = y2;

	for (int i = 0; i < 2; i++) {
		vertexData[i].color.r = 255;
		vertexData[i].color.g = 255;
		vertexData[i].color.b = 255;
		vertexData[i].color.a = 255;
	}

	GLuint indices[]{
		0, 1
	};

	vertexCount = sizeof(indices) / sizeof(*indices);

	upload(vertexData, sizeof(vertexData), indices, sizeof(indices));

}

void Line::upload(VertexStruct vertexData[], int sizeOfVertexData, GLuint indices[], int sizeOfIndices) {
	glBindVertexArray(_vaoID);
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _eboID);

	glBufferData(GL_ARRAY_BUFFER, sizeOfVertexData, vertexData, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(VertexStruct), (void*)offsetof(VertexStruct, position));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexStruct), (void*)offsetof(VertexStruct, color));
	glEnableVertexAttribArray(1);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfIndices, indices, GL_STATIC_DRAW);

	glBindVertexArray(0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Line::draw() {
	glBindVertexArray(_vaoID);
	glDrawElements(GL_LINES, vertexCount, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}
