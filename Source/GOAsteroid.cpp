#include "GOAsteroid.h"
#include "ParticleEmissionShape.h"
#include "AsteroidsGame.h"
#include "GameHandler.h"
#include <iostream>
#include <vector>

#include "GOParticleSystem.h"

std::vector<GOParticleSystem*> GOAsteroid::m_explodeParticles;

const std::vector<ParticleSpawnWrapper> GOAsteroid::part_w_explosion =
{
	{ 1, { ParticleTextureID::EXPLOSION, 1, VEC2_ZERO, VEC2_ZERO, VEC2_ZERO, VEC2_ONE * 0.5f, VEC2_ONE, { 0.5f, 0.5f, 64, 64 }, { 0.8f, 1.2f } } },
	{ 32, {ParticleTextureID::DEBRIS, 32, { -360, 360 }, { 2, 0.2f }, { 12, 7 }, VEC2_ZERO, VEC2_ONE, { 0.5f, 0.5f, 12, 8 }, { 0.8f, 2.0f }, { 0.3f, 1.5f }, { 0.3f, 1.5f }, VEC2_ONE, { 0.3f, 1.5f } } }
};

GOAsteroid::GOAsteroid(const Vector2 position, const float rotation, const Vector2Int size, const Vector2 velocity, const float torque, const bool createCollider) : GameObject(position, rotation, size, createCollider)
{
	m_currentVelocity = velocity;
	m_currentTorque = torque;
}

void GOAsteroid::FixedUpdate(float fixedTimeStep, float currentTime)
{
	this->GameObject::FixedUpdate(fixedTimeStep, currentTime);

	if (this->GameObject::DeleteIfOutsideScreen(40))
	{
		std::cout << "Deleted asteroid" << std::endl;
	}
}

void GOAsteroid::OnCollision(GameObject* other)
{
	this->GameObject::OnCollisionEnemy(other);
	if (other->GetID() == GameObjectID::SHOT)
		OnGetDestroyed(other);
}

void GOAsteroid::OnGetDestroyed(GameObject* other)
{
	EmitExplosion();
}

void GOAsteroid::EmitExplosion()
{
	GOParticleSystem* explosion = nullptr;

	for (int i = 0; i < m_explodeParticles.size(); i++)
	{
		if (m_explodeParticles[i]->GetState() == ParticleSystemState::STOPPED)
		{
			explosion = m_explodeParticles[i];
		}
	}

	// Create new explosion if none available
	if (!explosion)
	{
		CircleEmitterShape shape = { 4, 2 };
		explosion = new GOParticleSystem(part_w_explosion, shape, 5, false, false, true, m_position);
		m_explodeParticles.push_back(explosion);

		AsteroidsGame::AddObject(explosion);
	}

	explosion->SetPosition(m_position);
	explosion->Play();
}

GameObjectID GOAsteroid::GetID() { return GameObjectID::ASTEROID; }