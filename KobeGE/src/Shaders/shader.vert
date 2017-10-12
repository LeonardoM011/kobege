#version 130

in vec2 vertexPosition;
in vec4 vertexColor;

out vec4 fragmentColor;

void main() {
	gl_Position.xy = vertexPosition;
	gl_Position.z = 0;
	gl_Position.w = 1;
	fragmentColor = vertexColor;
}