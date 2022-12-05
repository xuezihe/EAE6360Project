#include "MyCamera.h"
#include <gtx\transform.hpp>

const float Camera::_MOVEMENT_SPEED = 0.1f;

Camera::Camera() :
	_viewDirection(0.0f, 0.0f, -1.0f),
	_UP(0.0f, 1.0f, 0.0f)
{
}

void Camera::mouseUpdate(const glm::vec2& newMousePosition)
{
	glm::vec2 mouseDelta = newMousePosition - _oldMousePosition;
	if (glm::length(mouseDelta) > 50.0f)
	{
		_oldMousePosition = newMousePosition;
		return;
	}
	const float ROTATIONAL_SPEED = 0.5f;
	_strafeDirection = glm::cross(_viewDirection, _UP);
	glm::mat4 rotator = glm::rotate(-mouseDelta.x * ROTATIONAL_SPEED, _UP) *
		glm::rotate(-mouseDelta.y * ROTATIONAL_SPEED, _strafeDirection);

	_viewDirection = glm::mat3(rotator) * _viewDirection;

	_oldMousePosition = newMousePosition;
}

glm::mat4 Camera::getWorldToViewMatrix() const
{
	return glm::lookAt(_position, _position + _viewDirection, _UP);
}

glm::vec3 Camera::getviewPostion() const
{
	return _position;
}

void Camera::moveForward()
{
	_position += _MOVEMENT_SPEED * _viewDirection;
}

void Camera::moveBackward()
{
	_position += -_MOVEMENT_SPEED * _viewDirection;
}

void Camera::strafeLeft()
{
	_position += -_MOVEMENT_SPEED * _strafeDirection;
}

void Camera::strafeRight()
{
	_position += _MOVEMENT_SPEED * _strafeDirection;
}

void Camera::moveUp()
{
	_position += _MOVEMENT_SPEED * _UP;
}

void Camera::moveDown()
{
	_position += -_MOVEMENT_SPEED * _UP;
}