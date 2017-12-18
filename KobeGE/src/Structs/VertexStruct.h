#pragma once
#include <GL/glew.h>

struct TexStruct {
	struct Position {
		GLdouble x;
		GLdouble y;
	};
	Position position;

	struct TexCoord {
		GLdouble x;
		GLdouble y;
	};
	TexCoord texCoord;
};

struct ColorStruct {
	struct Position {
		GLdouble x;
		GLdouble y;
	};
	Position position;

	struct Color {
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	};
	Color color;
};
