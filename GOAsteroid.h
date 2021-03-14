#pragma once
#include "GameObject.h"
#include "GameObjectID.h"
#include "Library.h"
#include <vector>

#include "GOParticleSystem.h"

class GOAsteroid : public GameObject
{
public:
	GOAsteroid(const Vector2 position, const float rotation, const Vector2Int size, const Vector2 velocity, const float torque, const bool createCollider);

	void FixedUpdate(float fixedTimeStep, float currentTime);

	GameObjectID GetID();

protected:
	void OnCollision(GameObject* other);

private:
	static std::vector<GOParticleSystem*> m_explodeParticles;

	void EmitExplosion();

	void OnGetDestroyed(GameObject* other);

	static const std::vector<ParticleSpawnWrapper> part_w_explosion;
};