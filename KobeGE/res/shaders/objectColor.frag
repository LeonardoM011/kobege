#version 330 core

in vec4 fragmentColor;
in vec2 texCoord;

layout (location = 0) out vec4 color;

uniform sampler2D textureData;

void main() {
	color = mix(texture(textureData, texCoord), fragmentColor, 0.3);
}