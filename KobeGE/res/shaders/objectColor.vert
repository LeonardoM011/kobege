#version 330 core

layout (location = 0) in vec2 vertexPosition;
layout (location = 1) in vec4 vertexColor;
layout (location = 2) in vec2 aTexCoord;

out vec4 fragmentColor;
out vec2 texCoord;

uniform mat4 view;
uniform mat4 model;

void main() {
	gl_Position = model * view * vec4(vertexPosition, 0.0, 1.0);
	fragmentColor = vertexColor;
	texCoord = aTexCoord;
}