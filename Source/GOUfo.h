#pragma once
#include "GameObject.h"
#include "GOPlayer.h"

class GOUfo : public GameObject
{
public:
	GOUfo(const Vector2 position, const float rotation, const Vector2Int size, GOPlayer* playerToTrack, const bool createCollider);

	GameObjectID GetID();

	void FixedUpdate(float fixedTimeStep, float currentTime);

private:
	GOPlayer* m_playerToTrack;

protected:
	void OnCollision(GameObject* other);
};