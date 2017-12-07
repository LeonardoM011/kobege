#pragma once
#include <GL/glew.h>
#include <cstddef>
#include <iostream>
#include <string>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include "Structs/ObjectStruct.h"
#include "Structs/VertexStruct.h"
#include "ErrorChecking/PrintError.h"
#include "Shaders/ShaderManager.h"
#include "ErrorChecking/PrintError.h"

class Object {
public:
	Object();
	~Object();
	virtual void init(ObjectStruct objInfo, std::string textureFilePath, int windowWidth, int windowHeight);
	void draw();
private:
	void upload(VertexStruct vertexData[], int sizeOfVertexData, GLuint indices[], int sizeOfIndices, std::string texturePath);
	GLuint _vboID;
	GLuint _vaoID;
	GLuint _eboID;
	GLuint _texID;
	int _vertexCount;
	static ShaderManager _shader;
	static bool _isShaderSetup;
	int _windowWidth;
	int _windowHeight;
	glm::mat4 _viewMatrix;
	glm::mat4 _modelMatrix;
protected:
	void generate(GLuint &vboID, GLuint &vaoID, GLuint &eboID, GLuint &texID);
};

