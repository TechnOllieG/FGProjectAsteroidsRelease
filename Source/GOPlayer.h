#pragma once
#include "GameObject.h"
#include "Input.h"

class GOParticleSystem;

class GOPlayer : public GameObject
{
public:
	GOPlayer(const Vector2 position, const float rotation, const Vector2Int size, Input* input);

	GameObjectID GetID();

	void FixedUpdate(float fixedTimeStep, float currentTime);

private:
	Input* m_input;
	float m_timeOfLastShot = 0.0f;
	const float m_shootCooldown = 0.2f;
	bool m_playingGasSound = false;

	GOParticleSystem* m_particleTest;
};