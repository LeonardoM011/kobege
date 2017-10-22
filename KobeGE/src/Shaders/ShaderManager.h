#pragma once
#include <GL/glew.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include "ErrorChecking/PrintError.h"

class ShaderManager {
public:
	ShaderManager();
	~ShaderManager();
	void compileShaders(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath);
	void addAtribute(const std::string attributeName);
	GLint getUniformLocation(const std::string &uniformName);
	void setUniform1f(GLuint location, GLfloat variable);
	void linkShaders();
	void startUsing();
	void stopUsing();
private:
	void checkForCompileErrors(GLuint &shaderID);
	void checkForLinkErrors();
	std::string openFile(const std::string &shaderFilePath);
	GLuint _programID;
	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;
	int _numAttribs;
};

