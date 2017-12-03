#include "Object.h"
#define STB_IMAGE_IMPLEMENTATION
#include "externcode/imageloader/stb_image.h"

Object::Object() :
	_vaoID(0),
	_vboID(0),
	_eboID(0)
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

void Object::init(ObjectStruct objInfo, std::string textureFilePath, ShaderManager *shader) {
	_shader = shader;

	generate(_vboID, _vaoID, _eboID, _texID);

	VertexStruct vertexData[4];

	float x = objInfo.x;
	float y = objInfo.y;
	float width = objInfo.width;
	float height = objInfo.height;

	vertexData[0].position.x = x + width;
	vertexData[0].position.y = y + height;
	vertexData[0].texCoord.x = 1.0f;
	vertexData[0].texCoord.y = 1.0f;

	vertexData[1].position.x = x + width;
	vertexData[1].position.y = y;
	vertexData[1].texCoord.x = 1.0f;
	vertexData[1].texCoord.y = 0.0f;

	vertexData[2].position.x = x;
	vertexData[2].position.y = y;
	vertexData[2].texCoord.x = 0.0f;
	vertexData[2].texCoord.y = 0.0f;

	vertexData[3].position.x = x;
	vertexData[3].position.y = y + height;
	vertexData[3].texCoord.x = 0.0f;
	vertexData[3].texCoord.y = 1.0f;
	
	for (int i = 0; i < 4; i++) {
		vertexData[i].color.r = 255;
		vertexData[i].color.g = 255;
		vertexData[i].color.b = 255;
		vertexData[i].color.a = 255;
	}

	GLuint indices[]{
		0, 1, 3,
		1, 2, 3
	};

	vertexCount = sizeof(indices) / sizeof(*indices);

	upload(vertexData, sizeof(vertexData), indices, sizeof(indices), textureFilePath);
	
	_shader->startUsing();
	_shader->setInt("textureData", 0);
	_shader->stopUsing();
}

void Object::upload(VertexStruct vertexData[], int sizeOfVertexData, GLuint indices[], int sizeOfIndices, std::string texturePath) {
	glBindVertexArray(_vaoID);

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeOfVertexData, vertexData, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfIndices, indices, GL_STATIC_DRAW);

	// ---- Textures ----
	glBindTexture(GL_TEXTURE_2D, _texID);
	// Some tex parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Loading Texture
	int width, height, bpp;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *textureData = stbi_load(texturePath.c_str(), &width, &height, &bpp, 0);
	// Error Checking and loading data to shader
	if (textureData) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		PrintError::PrintLn(10, "Failed to load texture: " + texturePath);
	}
	// Freeing image data
	stbi_image_free(textureData);


	
	// Position
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(VertexStruct), (void*)offsetof(VertexStruct, position));
	glEnableVertexAttribArray(0);

	// Color
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexStruct), (void*)offsetof(VertexStruct, color));
	glEnableVertexAttribArray(1);

	// TexCoord
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexStruct), (void*)offsetof(VertexStruct, texCoord));
	glEnableVertexAttribArray(2);

	
	//glDisableVertexAttribArray(0);
	//glDisableVertexAttribArray(1);
	//glDisableVertexAttribArray(2);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);

	
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
	_shader->startUsing();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texID);

	glm::mat4 transform;
	transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
	transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

	unsigned int transformLoc = glGetUniformLocation(_shader->getID(), "transform");
	if (transformLoc == GL_INVALID_INDEX) PrintError::PrintLn(5, "Uniform location not found");

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
	
	glBindVertexArray(_vaoID);
	glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);

	_shader->stopUsing();
}
