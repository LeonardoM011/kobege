#include "Player.h"

Player::Player() {

}

Player::~Player() {

}

void Player::init(glm::vec2 pos, GLdouble width, GLdouble height, ShaderManager shader, int windowWidth, int windowHeight, GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
	_playerObject.init(pos, width, height, shader, windowWidth, windowHeight, r, g, b, a);
}

void Player::draw() {
	handleEvents();
	_playerObject.draw();
}

void Player::handleEvents() {
	if (InputManager::keydown[GLFW_KEY_W]) {
		_playerObject.move(glm::vec3(0.0f, 0.0003f, 0.0f));
		float upperCorner = _playerObject.getPos().y + _playerObject.getHeight() * 0.5;
		if (upperCorner >= 1.0f) {
			_playerObject.move(glm::vec3(0.0f, -(upperCorner - 1.0f), 0.0f));
		}
	}

	if (InputManager::keydown[GLFW_KEY_S]) {
		_playerObject.move(glm::vec3(0.0f, -0.0003f, 0.0f));
		float lowerCorner = _playerObject.getPos().y + _playerObject.getHeight() * -0.5;
		if (lowerCorner <= -1.0f) {
			_playerObject.move(glm::vec3(0.0f, -(lowerCorner + 1.0f), 0.0f));
		}
	}
}

