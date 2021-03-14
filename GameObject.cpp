#include "GameObject.h"
#include "Collider.h"
#include "GameHandler.h"
#include "AsteroidsGame.h"

GameObject::GameObject(const Vector2 position, const float rotation, const Vector2Int size, const bool createCollider)
{
	SetRotation(rotation);

	m_size = size;

	m_isVisible = true;

	m_rect = SDL_Rect{ 0, 0, m_size.x, m_size.y };
	SetPosition(position);
	int biggestSize = (size.x > size.y ? size.x : size.y) * 0.5f;

	if(createCollider)
		m_collider = new Collider(this, biggestSize, [this](GameObject* gID) { OnCollision(gID); });
}

void GameObject::CreateCollider()
{
	int biggestSize = (m_size.x > m_size.y ? m_size.x : m_size.y) * 0.5f;
	m_collider = new Collider(this, biggestSize, [this](GameObject* gID) { OnCollision(gID); });
}

GameObject::~GameObject()
{
	//std::cout << "Deleted GameObject with ID of " << typeid(GetID()).name() << std::endl;
	if (m_collider && m_collider != nullptr)
	{
		delete m_collider;
		m_collider = nullptr;
	}
}

void GameObject::SetPosition(Vector2 position)
{
	m_position = position;
	m_rect.x = position.x - m_rect.w * 0.5f;
	m_rect.y = position.y - m_rect.h * 0.5f;

	if (m_collider && m_detectCollisions)
		m_collider->DetectCollision();
}

void GameObject::SetSize(Vector2Int size)
{
	m_size = size;
	m_rect.w = size.x;
	m_rect.h = size.y;

	SetPosition(m_position);
}

void GameObject::SetRotation(float rotation)
{
	m_rotation = fmod<float>(rotation, 360.0f);
	CalculateForward();
}

void GameObject::SetCollidable(bool state)
{
	m_collider->isCollidable = state;
}

void GameObject::OnCollisionEnemy(GameObject* other)
{
	switch (other->GetID())
	{
	case GameObjectID::SHOT:
		AudioManager::PlaySound(AudioID::EXPLOSION);
		AsteroidsGame::AddPoint();
		this->SetCollidable(false);
		other->SetCollidable(false);
		AsteroidsGame::ReturnObject(this);
		AsteroidsGame::ReturnObject(other);
		break;
	case GameObjectID::PLAYER:
		if (AsteroidsGame::IsPlayerInvulnerable())
			return;

		AudioManager::PlaySound(AudioID::EXPLOSION);
		if (AsteroidsGame::GetLives() > 1)
		{
			AsteroidsGame::LooseLife();
			return;
		}

		std::cout << "Game Over!" << std::endl;
		AsteroidsGame::OnGameOver();
		break;
	}
}

void GameObject::FixedUpdate(float fixedTimeStep, float currentTime)
{
	// Add current torque to rotation
	if (m_currentTorque > 0.01f || m_currentTorque < -0.01f)
	{
		SetRotation(GetRotation() + m_currentTorque);
	}

	// Add current velocity to position
	if (m_currentVelocity.sqrMagnitude() > 0.01f)
	{
		SetPosition(m_position + m_currentVelocity);
	}
}

bool GameObject::DeleteIfOutsideScreen(float additionalMargin)
{
	Vector2Int pos = GetPosition();
	Vector2Int size = GetSize();
	Vector2Int resolution = GameHandler::GetResolution();
	float margin = size.x * 0.5f + additionalMargin;

	bool aboveScreen = pos.y < -margin;
	bool belowScreen = pos.y > resolution.y + margin;
	bool leftOfScreen = pos.x < -margin;
	bool rightOfScreen = pos.x > resolution.x + margin;

	if (aboveScreen || belowScreen || leftOfScreen || rightOfScreen)
	{
		AsteroidsGame::ReturnObject(this);
		return true;
	}
	return false;
}

void GameObject::Update(float deltaTime, float currentTime)
{

}

void GameObject::CalculateForward()
{
	float rad = m_rotation * deg2Rad;

	forward = Vector2(sin(rad), -cos(rad));
}