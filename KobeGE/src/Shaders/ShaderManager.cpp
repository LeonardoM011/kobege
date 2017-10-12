#include "ShaderManager.h"

ShaderManager::ShaderManager() : 
	_programID(0),
	_vertexShaderID(0),
	_fragmentShaderID(0),
	_numAttribs(0)
{

}

ShaderManager::~ShaderManager() {

}

std::string ShaderManager::openFile(const std::string &shaderFilePath) {
	std::string fileContents = "", line = "";

	std::ifstream shaderFile(shaderFilePath);
	if (shaderFile.fail()) {
		PrintError::PrintLn(4, "File: \"" + shaderFilePath + "\" se ne moze otvoriti");
		return "";
	}

	while (std::getline(shaderFile, line)) {
		fileContents += line + "\n";
	}

	shaderFile.close();

	return fileContents;
}

void ShaderManager::checkForCompileErrors(GLuint &shaderID) {
	GLint success = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);
		glDeleteShader(shaderID);
		std::printf("%s\n", &(errorLog[0]));
	}
}

void ShaderManager::checkForLinkErrors() {
	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);

	if (isLinked == GL_FALSE) {
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<char> errorLog(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);
		glDeleteProgram(_programID);
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);
		std::printf("%s\n", &(errorLog[0]));
	}
}

void ShaderManager::linkShaders() {
	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);

	glLinkProgram(_programID);

	checkForLinkErrors();

	glDetachShader(_programID, _vertexShaderID);
	glDetachShader(_programID, _fragmentShaderID);
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
}

void ShaderManager::compileShaders(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath) {
	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	_programID = glCreateProgram();

	std::string vertexShaderContents = openFile(vertexShaderFilePath);
	std::string fragmentShaderContents = openFile(fragmentShaderFilePath);

	const char* vertexContentsInC = vertexShaderContents.c_str();
	const char* fragmentContentsInC = fragmentShaderContents.c_str();

	glShaderSource(_vertexShaderID, 1, &vertexContentsInC, nullptr);
	glCompileShader(_vertexShaderID);
	checkForCompileErrors(_vertexShaderID);

	glShaderSource(_fragmentShaderID, 1, &fragmentContentsInC, nullptr);
	glCompileShader(_fragmentShaderID);
	checkForCompileErrors(_fragmentShaderID);
}

void ShaderManager::addAtribute(const std::string attributeName) {
	glBindAttribLocation(_programID, _numAttribs, attributeName.c_str());
	_numAttribs++;
}

GLint ShaderManager::getUniformLocation(const std::string &uniformName) {
	GLint location = glGetUniformLocation(_programID, uniformName.c_str());
	if (location == GL_INVALID_INDEX) return PrintError::PrintLn(5, "Uniform location " + uniformName + " nije pronadjen");
	return location;
}

void ShaderManager::setUniform1f(GLuint location, GLfloat variable) {
	glUniform1f(location, variable);
}

void ShaderManager::startUsing() {
	glUseProgram(_programID);
	for (int i = 0; i < _numAttribs; i++) {
		glDisableVertexAttribArray(i);
	}
}

void ShaderManager::stopUsing() {
	glUseProgram(0);
	for (int i = 0; i < _numAttribs; i++) {
		glDisableVertexAttribArray(i);
	}
}
