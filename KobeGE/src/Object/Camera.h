#pragma once
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <vector>
#include "Shaders/ShaderManager.h"

class Camera {
public:
	Camera();
	~Camera();
	void addShader(ShaderManager &shader);
	void move(glm::vec3 pos);
private:
	std::vector<ShaderManager> _shader;
	glm::mat4 _viewMatrix;
};

