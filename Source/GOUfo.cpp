#include "GOUfo.h"
#include "AudioManager.h"
#include <iostream>
#include "AsteroidsGame.h"

GOUfo::GOUfo(const Vector2 position, const float rotation, const Vector2Int size, GOPlayer* playerToTrack, const bool createCollider) : GameObject(position, rotation, size, createCollider)
{
	m_currentVelocity = VEC2_ZERO;
	m_currentTorque = 0;
	m_playerToTrack = playerToTrack;
	m_maxMovementSpeed = 1.0f;
}

void GOUfo::FixedUpdate(float fixedTimeStep, float currentTime)
{
	Vector2 direction = (m_playerToTrack->GetPosition() - GetPosition()).normalized();
	m_currentVelocity = direction * m_maxMovementSpeed;

	this->GameObject::FixedUpdate(fixedTimeStep, currentTime);
}

void GOUfo::OnCollision(GameObject* other)
{
	this->GameObject::OnCollisionEnemy(other);
}

GameObjectID GOUfo::GetID()
{
	return GameObjectID::UFO;
}