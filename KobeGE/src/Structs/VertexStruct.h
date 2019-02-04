#pragma once
#include <GL/glew.h>

struct Vector2d {
	GLdouble x;
	GLdouble y;
};

struct TexStruct {
	Vector2d position;
	Vector2d texCoord;
};

struct ColorStruct {
	Vector2d position;

	struct Color {
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	};
	Color color;
};
