#pragma once
#include "GameObject.h"

class GOBackground : public GameObject
{
public:
	GOBackground();

	void FixedUpdate(float fixedTimeStep, float currentTime) {}

	GameObjectID GetID();
};