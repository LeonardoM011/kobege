#pragma once
#include <GL/glew.h>

struct VertexStruct {
	struct Position {
		float x;
		float y;
	};
	Position position;

	struct Color {
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	};
	Color color;

	struct TexCoord {
		float x;
		float y;
	};
	TexCoord texCoord;
};
