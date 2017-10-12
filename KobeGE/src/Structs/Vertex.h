#pragma once
#include <GL/glew.h>

struct Vertex {
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
};
