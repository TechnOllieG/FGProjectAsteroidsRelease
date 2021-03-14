#include "GOPlayer.h"
#include "GOShot.h"
#include "GameHandler.h"
#include "AsteroidsGame.h"

GOPlayer::GOPlayer(const Vector2 position, const float rotation, const Vector2Int size, Input* input) : GameObject(position, rotation, size)
{
	m_currentVelocity = VEC2_ZERO;
	m_rotationSpeed = 5.0f;
	m_movementSpeed = 0.1f;
	m_maxMovementSpeed = 3.0f;
	m_input = input;
	m_detectCollisions = false;
}

void GOPlayer::FixedUpdate(float fixedTimeStep, float currentTime)
{
	m_currentTorque = 0;

	if (m_input->m_gas)
	{
		if (!m_playingGasSound)
		{
			AudioManager::PlaySoundLooped(AudioID::GAS);
			m_playingGasSound = true;
		}

		// Add speed to the current velocity based on player's forward direction.
		m_currentVelocity += forward * m_movementSpeed;

		if (m_currentVelocity.sqrMagnitude() > m_maxMovementSpeed * m_maxMovementSpeed)
		{
			m_currentVelocity = m_currentVelocity.normalized() * m_maxMovementSpeed;
		}
	}
	else if (m_playingGasSound)
	{
		AudioManager::StopLoopedSound(AudioID::GAS, 250);
		m_playingGasSound = false;
	}

	if (m_input->m_rotateLeft)
	{
		// Anti-clockwise rotation
		m_currentTorque = -m_rotationSpeed;
	}
	if (m_input->m_rotateRight)
	{
		// Clockwise rotation
		m_currentTorque = m_rotationSpeed;
	}
	if (m_input->m_shoot && currentTime - m_timeOfLastShot > m_shootCooldown)
	{
		m_timeOfLastShot = currentTime;
		// Add a bullet object in front of the player and fire it

		// AsteroidsGame::AddObject(new GOShot(ConvertToVector2(GetPosition()) + forward * (GetSize().y * 0.5f), GetRotation(), Vector2Int(20, 20), m_currentVelocity));

		AudioManager::PlaySound(AudioID::SHOOT);

		GOShot* shot = (GOShot*) AsteroidsGame::GetObject(GameObjectID::SHOT);
		shot->SetCollidable(true);
		shot->SetPosition(ConvertToVector2(GetPosition()) + forward * (GetSize().y * 0.5f));
		shot->SetRotation(GetRotation());

		float currentSpeedInDirection = Vector2::Dot(forward, m_currentVelocity);
		shot->m_currentVelocity = forward * (5.0f + currentSpeedInDirection);

		shot->SetSize(Vector2Int(20, 20));
		AsteroidsGame::AddObject(shot);
	}

	this->GameObject::FixedUpdate(fixedTimeStep, currentTime);

	Vector2 resolution = GameHandler::GetResolution();

	if (m_position.y < 0)
		SetPosition(Vector2(m_position.x, resolution.y));

	if (m_position.y > resolution.y)
		SetPosition(Vector2(m_position.x, 0));

	if (m_position.x < 0)
		SetPosition(Vector2(resolution.x, m_position.y));

	if (m_position.x > resolution.x)
		SetPosition(Vector2(0, m_position.y));
}

GameObjectID GOPlayer::GetID() { return GameObjectID::PLAYER; }