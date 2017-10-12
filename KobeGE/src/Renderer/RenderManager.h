#pragma once
#include <GL/glew.h>

class RenderManager {
public:
	RenderManager();
	~RenderManager();
	void init();
private:
	GLuint _vboID;
};

