#pragma once
#include <GL/glew.h>
#include <GLM/glm.hpp>
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
	/*GLint getUniformLocation(const std::string &uniformName);
	void setUniform1f(GLuint location, GLfloat variable);*/
	void linkShaders();
	void startUsing();
	void stopUsing();
	GLuint getID();

	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setVec2(const std::string &name, float x, float y) const;
	void setVec2(const std::string &name, const glm::vec2 &value) const;
	void setVec3(const std::string &name, float x, float y, float z) const;
	void setVec3(const std::string &name, const glm::vec3 &value) const;
	void setVec4(const std::string &name, float x, float y, float z, float w);
	void setVec4(const std::string &name, const glm::vec4 &value) const;
	void setMat2(const std::string &name, const glm::mat2 &mat) const;
	void setMat3(const std::string &name, const glm::mat3 &mat) const;
	void setMat4(const std::string &name, const glm::mat4 &mat) const;
private:
	void checkForCompileErrors(GLuint &shaderID);
	void checkForLinkErrors();
	std::string openFile(const std::string &shaderFilePath);
	GLuint _programID;
	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;
	int _numAttribs;
};
