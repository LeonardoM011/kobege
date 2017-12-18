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
	void init(glm::vec2 pos, GLdouble width, GLdouble height, int windowWidth, int windowHeight, std::string textureFilePath);
	void init(glm::vec2 pos, GLdouble width, GLdouble height, int windowWidth, int windowHeight, GLubyte r, GLubyte g, GLubyte b, GLubyte a);
	void draw();
	void move(glm::vec3 pos);
	void rotate(float angle, glm::vec3 axis);
	glm::vec2 getPos() {
		return glm::vec2(_modelMatrix[3][0], _modelMatrix[3][1]);
	}
	GLdouble getWidth() {
		return _width;
	}
	GLdouble getHeight() {
		return _height;
	}
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
	GLdouble _width;
	GLdouble _height;
	void printMatrix(glm::mat4 mat) {
		std::printf("%f | %f | %f | %f\n", mat[0][0], mat[0][1], mat[0][2], mat[0][3]);
		std::printf("%f | %f | %f | %f\n", mat[1][0], mat[1][1], mat[1][2], mat[1][3]);
		std::printf("%f | %f | %f | %f\n", mat[2][0], mat[2][1], mat[2][2], mat[2][3]);
		std::printf("%f | %f | %f | %f\n", mat[3][0], mat[3][1], mat[3][2], mat[3][3]);
		std::printf("\n");
	}
};

