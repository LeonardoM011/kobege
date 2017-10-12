#include "Object.h"

Object::Object(float x, float y, float width, float height) :
	_vboID(0),
	_tempTime(0.0f)
{
	objInfo.x = x;
	objInfo.y = y;
	objInfo.width = width;
	objInfo.height = height;
	shader.compileShaders("src/Shaders/shader.vert", "src/Shaders/shader.frag");
	shader.addAtribute("vertexPosition");
	shader.addAtribute("vertexColor");
	shader.linkShaders();

	if (_vboID == 0)
		glGenBuffers(1, &_vboID);

	Vertex vertexData[6];

	vertexData[0].position.x = x + width;
	vertexData[0].position.y = y + height;

	vertexData[1].position.x = x;
	vertexData[1].position.y = y + height;

	vertexData[2].position.x = x;
	vertexData[2].position.y = y;

	vertexData[3].position.x = x;
	vertexData[3].position.y = y;

	vertexData[4].position.x = x + width;
	vertexData[4].position.y = y;

	vertexData[5].position.x = x + width;
	vertexData[5].position.y = y + height;



	for (int i = 0; i < 6; i++) {
		vertexData[i].color.r = 255;
		vertexData[i].color.g = 255;
		vertexData[i].color.b = 0;
		vertexData[i].color.a = 255;
	}

	vertexData[1].color.r = 255;
	vertexData[1].color.g = 0;
	vertexData[1].color.b = 0;
	vertexData[1].color.a = 255;

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Object::~Object() {
	if (_vboID != 0)
		glDeleteBuffers(1, &_vboID);
}

void Object::draw() {
	shader.startUsing();

	_tempTime += 0.001f;
	shader.setUniform1f(shader.getUniformLocation("time"), _tempTime);

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	shader.stopUsing();
}
