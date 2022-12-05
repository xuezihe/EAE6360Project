#pragma once
#include"glm.hpp"

class Camera
{
	glm::vec3 _position;
	glm::vec3 _viewDirection;
	const glm::vec3 _UP;
	glm::vec2 _oldMousePosition;
	static const float _MOVEMENT_SPEED;
	glm::vec3 _strafeDirection;
	float _zoom = 45.0f;

public:
	Camera();
	void mouseUpdate(const glm::vec2& newMousePosition);
	glm::mat4 getWorldToViewMatrix() const;
	glm::vec3 getviewPostion() const;
	
	void moveForward();
	void moveBackward();
	void strafeLeft();
	void strafeRight();
	void moveUp();
	void moveDown();
	float zoom() { return _zoom; }
};

