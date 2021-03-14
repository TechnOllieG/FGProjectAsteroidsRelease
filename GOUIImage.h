#pragma once
#include "GameObject.h"

class GOUIImage : public GameObject
{
public:
	GOUIImage(Vector2 position, float roation, Vector2Int size, GameObjectID texture);

	GameObjectID GetID();

	void FixedUpdate(float fixedTimeStep, float currentTime) {}

	void ChangeTexture(GameObjectID texture);

private:
	GameObjectID m_textureID;
};