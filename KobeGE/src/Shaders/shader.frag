#version 330 core

in vec4 fragmentColor;
in vec4 gl_FragCoord;

layout (location = 0) out vec4 color;

//uniform float time;

void main() {
	//color = (fragmentColor + vec4(1.0 * (cos(time) + 1.0) * 0.5, 1.0 * (cos(time + 2.0) + 1.0) * 0.5, 1.0 * (sin(time + 1.0) + 1.0) * 0.5, 0.0)) / 2.0;
	highp int temp = int(int(mod(floor(gl_FragCoord.x), 12)) < 9);
	color = vec4(temp, temp, temp, 1.0);
}