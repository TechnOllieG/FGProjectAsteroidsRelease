#pragma once
#include "GameObject.h"

class GOShot : public GameObject
{
public:
	GOShot(const Vector2 position, const float rotation, const Vector2Int size, const Vector2 playerVelocity, const bool createCollider);

	void FixedUpdate(float fixedTimeStep, float currentTime);

	GameObjectID GetID();
};