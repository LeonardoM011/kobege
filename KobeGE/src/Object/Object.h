#pragma once
#include <GL/glew.h>
#include <cstddef>
#include <iostream>
#include <string>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include "Structs/VertexStruct.h"
#include "ErrorChecking/PrintError.h"
#include "Shaders/ShaderManager.h"
#include "ErrorChecking/PrintError.h"

class Object {
public:
	Object();
	~Object();
	void init(glm::vec2 pos, GLdouble width, GLdouble height, ShaderManager shader, int windowWidth, int windowHeight, std::string textureFilePath);
	void init(glm::vec2 pos, GLdouble width, GLdouble height, ShaderManager shader, int windowWidth, int windowHeight, GLubyte r, GLubyte g, GLubyte b, GLubyte a);
	void draw();
	void move(glm::vec3 pos);
	void rotate(float angle, glm::vec3 axis);
private:
	void upload(TexStruct vertexData[], int sizeOfVertexData, GLuint indices[], int sizeOfIndices, std::string texturePath);
	void upload(ColorStruct vertexData[], int sizeOfVertexData, GLuint indices[], int sizeOfIndices);
	void generate(GLuint &vboID, GLuint &vaoID, GLuint &eboID, GLuint &texID);
	GLuint _vboID;
	GLuint _vaoID;
	GLuint _eboID;
	GLuint _texID;
	int _vertexCount;
	ShaderManager _shader;
	int _windowWidth;
	int _windowHeight;
	glm::mat4 _modelMatrix;
};

