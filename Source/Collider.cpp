#include "Collider.h"

//#include <functional>
//#include <vector>

std::vector<Collider*> Collider::m_allColliders;

Collider::Collider(GameObject* gameObject, int radius, CollisionCallback onCollisionEvent)
{
	m_onCollision = onCollisionEvent;

	m_pixelRadius = radius;

	m_gameObject = gameObject;

	m_position = &m_gameObject->m_position;

	isCollidable = true;

	m_allColliders.push_back(this);
	m_vecIndex = m_allColliders.size() - 1;
}

Collider::Collider(Vector2 position, int radius)
{
	m_gameObject = nullptr;

	m_position = new Vector2{ position.x, position.y };

	m_pixelRadius = radius;

	isCollidable = true;

	m_allColliders.push_back(this);
	m_vecIndex = m_allColliders.size() - 1;
}

Collider::~Collider()
{
	// If the collider is orphaned, delete the Vector2
	// that it created.
	if (m_gameObject == nullptr)
	{
		delete m_position;
	}

	// Lowering the index of all colliders next in the list
	// (Otherwise we go out of range)
	for (int i = m_vecIndex + 1; i < m_allColliders.size(); i++)
	{
		m_allColliders[i]->m_vecIndex--;
	}

	m_allColliders.erase(m_allColliders.begin() + m_vecIndex);
}

void Collider::SetPosition(const Vector2 newPosition)
{
	*m_position = newPosition;

	if (isCollidable)
		DetectCollision();
}

void Collider::Translate(const Vector2 translation)
{
	SetPosition(*m_position + translation);
}

void Collider::DetectCollision()
{
	//std::cout << "101010101010 scooby doo" << std::endl;

	if (m_allColliders.size() > 1 && &m_onCollision != nullptr)
	{
		for (int i = 0; i < m_allColliders.size(); i++)
		{
			Collider* other = m_allColliders[i];

			if (!other->isCollidable)
				continue;

			if (m_position == nullptr || other->m_position == nullptr)
				continue;

			//std::cout << Vector2::Distance(*m_position, *other->m_position) << std::endl;

			if (other != this && Vector2::Distance(*m_position, *other->m_position) <= m_pixelRadius)
			{
				//std::cout << (int)other->m_gameObject->GetID() << std::endl;
				m_onCollision(other->m_gameObject);
			}
		}
	}
}