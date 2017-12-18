#include "Camera.h"

Camera::Camera() :
	_viewMatrix(1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f)
{

}

Camera::~Camera() {

}

void Camera::addShader(ShaderManager &shader) {
	shader.startUsing();
	shader.setMat4("view", _viewMatrix);
	shader.stopUsing();
	_shader.push_back(shader);
}

void Camera::move(glm::vec3 pos) {
	_viewMatrix = glm::translate(_viewMatrix, glm::vec3(-pos.x, -pos.y, -pos.z));
	for (ShaderManager s : _shader) {
		s.startUsing();
		s.setMat4("view", _viewMatrix);
		s.stopUsing();
	}
}
