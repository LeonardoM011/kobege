#version 330 core

layout (location = 0) in vec2 vertexPosition;
layout (location = 1) in vec2 aTexCoord;

out vec2 texCoord;

uniform mat4 view;
uniform mat4 model;

void main() {
	//gl_Position = model * view * vec4(vertexPosition, 0.0, 1.0);
	gl_Position = model * vec4(vertexPosition, 0.0, 1.0);
	texCoord = aTexCoord;
}