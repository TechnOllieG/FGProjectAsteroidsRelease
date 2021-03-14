#include "GOShot.h"
#include <vector>
#include <iostream>
#include "GameHandler.h"
#include "AsteroidsGame.h"

GOShot::GOShot(const Vector2 position, const float rotation, const Vector2Int size, const Vector2 playerVelocity, const bool createCollider) : GameObject(position, rotation, size, createCollider)
{
	float currentSpeedInDirection = Vector2::Dot(forward, playerVelocity);
	m_currentVelocity = forward * (5.0f + currentSpeedInDirection);
	m_rotationSpeed = 0.0f;
	m_movementSpeed = 0.0f;
	m_maxMovementSpeed = 0.0f;
	m_detectCollisions = false;
}

void GOShot::FixedUpdate(float fixedTimeStep, float currentTime)
{
	this->GameObject::FixedUpdate(fixedTimeStep, currentTime);

	if (this->GameObject::DeleteIfOutsideScreen())
	{
		std::cout << "Deleted shot" << std::endl;
	}
}

GameObjectID GOShot::GetID() { return GameObjectID::SHOT; }