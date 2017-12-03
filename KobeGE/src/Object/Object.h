#pragma once
#include <GL/glew.h>
#include <cstddef>
#include <iostream>
#include <string>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Structs/ObjectStruct.h"
#include "Structs/VertexStruct.h"
#include "ErrorChecking/PrintError.h"
#include "Shaders/ShaderManager.h"
#include "ErrorChecking/PrintError.h"

class Object {
public:
	Object();
	~Object();
	virtual void init(ObjectStruct objInfo, std::string textureFilePath, ShaderManager *shader);
	void draw();
private:
	void upload(VertexStruct vertexData[], int sizeOfVertexData, GLuint indices[], int sizeOfIndices, std::string texturePath);
	GLuint _vboID;
	GLuint _vaoID;
	GLuint _eboID;
	GLuint _texID;
	int vertexCount;
	ShaderManager *_shader;
protected:
	void generate(GLuint &vboID, GLuint &vaoID, GLuint &eboID, GLuint &texID);
};

