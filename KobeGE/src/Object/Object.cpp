#include "Object.h"
#define STB_IMAGE_IMPLEMENTATION
#include "externcode/imageloader/stb_image.h"

Object::Object() :
	_vaoID(0),
	_vboID(0),
	_eboID(0),
	_texID(0),
	_vertexCount(0),
	_windowWidth(0),
	_windowHeight(0),
	_width(0),
	_height(0),
	_modelMatrix	   (1.0f, 0.0f, 0.0f, 0.0f,
						0.0f, 1.0f, 0.0f, 0.0f,
						0.0f, 0.0f, 1.0f, 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f)
{
	
}

Object::~Object() {
	if (_vaoID != 0)
		glDeleteVertexArrays(1, &_vaoID);
	if (_vboID != 0)
		glDeleteBuffers(1, &_vboID);
	if (_eboID != 0)
		glDeleteBuffers(1, &_eboID);
	if (_texID != 0)
		glDeleteTextures(1, &_texID);
}

void Object::init(glm::vec2 pos, GLdouble width, GLdouble height, int windowWidth, int windowHeight, std::string textureFilePath) {
	_windowHeight = windowHeight;
	_windowWidth = windowWidth;
	_width = width;
	_height = height;

	_shader.compileShaders("res/shaders/ObjectTextureShader.vert", "res/shaders/ObjectTextureShader.frag");
	_shader.linkShaders();

	generate(_vboID, _vaoID, _eboID, _texID);

	TexStruct vertexData[4];

	vertexData[0].position.x = width * 0.5;
	vertexData[0].position.y = height * 0.5;
	vertexData[0].texCoord.x = 1.0f;
	vertexData[0].texCoord.y = 1.0f;

	vertexData[1].position.x = width * 0.5;
	vertexData[1].position.y = height * -0.5;
	vertexData[1].texCoord.x = 1.0f;
	vertexData[1].texCoord.y = 0.0f;

	vertexData[2].position.x = width * -0.5;
	vertexData[2].position.y = height * -0.5;
	vertexData[2].texCoord.x = 0.0f;
	vertexData[2].texCoord.y = 0.0f;

	vertexData[3].position.x = width * -0.5;
	vertexData[3].position.y = height * 0.5;
	vertexData[3].texCoord.x = 0.0f;
	vertexData[3].texCoord.y = 1.0f;

	move(glm::vec3(pos.x, pos.y, 0.0f));

	GLuint indices[]{
		0, 1, 3,
		1, 2, 3
	};

	_vertexCount = sizeof(indices) / sizeof(*indices);

	upload(vertexData, sizeof(vertexData), indices, sizeof(indices), textureFilePath);

	// I'm not sure if this is needed
	/*_textureShader.startUsing();
	_textureShader.setInt("textureData", 0);
	_textureShader.stopUsing();*/
}

void Object::init(glm::vec2 pos, GLdouble width, GLdouble height, int windowWidth, int windowHeight, GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
	_windowHeight = windowHeight;
	_windowWidth = windowWidth;
	_width = width;
	_height = height;

	_shader.compileShaders("res/shaders/ObjectColorShader.vert", "res/shaders/ObjectColorShader.frag");
	_shader.linkShaders();

	generate(_vboID, _vaoID, _eboID, _texID);

	ColorStruct vertexData[4];

	vertexData[0].position.x = width * 0.5;
	vertexData[0].position.y = height * 0.5;

	vertexData[1].position.x = width * 0.5;
	vertexData[1].position.y = height * -0.5;

	vertexData[2].position.x = width * -0.5;
	vertexData[2].position.y = height * -0.5;

	vertexData[3].position.x = width * -0.5;
	vertexData[3].position.y = height * 0.5;

	move(glm::vec3(pos.x, pos.y, 0.0f));

	for (int i = 0; i < 4; i++) {
		vertexData[i].color.r = r;
		vertexData[i].color.g = g;
		vertexData[i].color.b = b;
		vertexData[i].color.a = a;
	}

	GLuint indices[]{
		0, 1, 3,
		1, 2, 3
	};

	_vertexCount = sizeof(indices) / sizeof(*indices);

	upload(vertexData, sizeof(vertexData), indices, sizeof(indices));
}

void Object::upload(TexStruct vertexData[], int sizeOfVertexData, GLuint indices[], int sizeOfIndices, std::string texturePath) {
	// Binding all this to a VAO list
	glBindVertexArray(_vaoID);

	// Vertices buffer array
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeOfVertexData, vertexData, GL_STATIC_DRAW);
	
	// Elements buffer array
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfIndices, indices, GL_STATIC_DRAW);

	// Position
	glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, sizeof(TexStruct), (void*)offsetof(TexStruct, position));
	glEnableVertexAttribArray(0);
	
	// TexCoord
	glVertexAttribPointer(1, 2, GL_DOUBLE, GL_FALSE, sizeof(TexStruct), (void*)offsetof(TexStruct, texCoord));
	glEnableVertexAttribArray(1);


	// ---- Textures ----
	glBindTexture(GL_TEXTURE_2D, _texID);
	// Some Tex Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Loading Texture
	int width, height, bpp;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *textureData = stbi_load(texturePath.c_str(), &width, &height, &bpp, 0);
	// Error Checking and Loading Data to Shader
	if (textureData) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		PrintError::PrintLn(10, "Failed to load texture: " + texturePath);
	}
	// Freeing image data
	stbi_image_free(textureData);

	// Unbinding Everything
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Object::upload(ColorStruct vertexData[], int sizeOfVertexData, GLuint indices[], int sizeOfIndices) {
	// Binding all this to a VAO list
	glBindVertexArray(_vaoID);

	// Vertices buffer array
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeOfVertexData, vertexData, GL_STATIC_DRAW);

	// Elements buffer array
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfIndices, indices, GL_STATIC_DRAW);

	// Position
	glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, sizeof(ColorStruct), (void*)offsetof(ColorStruct, position));
	glEnableVertexAttribArray(0);

	// Color
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(ColorStruct), (void*)offsetof(ColorStruct, color));
	glEnableVertexAttribArray(1);

	// Unbinding Everything
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}


void Object::generate(GLuint &vboID, GLuint &vaoID, GLuint &eboID, GLuint &texID) {
	if (vaoID == 0)
		glGenVertexArrays(1, &vaoID);
	if (vboID == 0)
		glGenBuffers(1, &vboID);
	if (eboID == 0)
		glGenBuffers(1, &eboID);
	if (texID == 0)
		glGenTextures(1, &texID);
}

void Object::draw() {
	_shader.startUsing();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texID);

	glBindVertexArray(_vaoID);
	glDrawElements(GL_TRIANGLES, _vertexCount, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);

	_shader.stopUsing();
}

void Object::move(glm::vec3 pos) {
	_modelMatrix = glm::translate(_modelMatrix, pos);
	_shader.startUsing();
	_shader.setMat4("model", _modelMatrix);
	_shader.stopUsing();
}

void Object::rotate(float angle, glm::vec3 axis) {
	_modelMatrix = glm::rotate(_modelMatrix, angle, axis);
	_shader.startUsing();
	_shader.setMat4("model", _modelMatrix);
	_shader.stopUsing();
}


