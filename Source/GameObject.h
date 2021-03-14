#pragma once
#include <string>
#include "Library.h"
#include "SDL.h"
#include "SDL_image.h"
#include "GameObjectID.h"

class Collider;

class GameObject
{
protected:
	// Should the object be drawn on the screen?
	bool m_isVisible;

	Collider* m_collider = nullptr;

	void CalculateForward();

	bool DeleteIfOutsideScreen(float additionalMargin = 0);

	bool m_detectCollisions = true;

	// The euler rotation of the object on the Z-axis.
	float m_rotation;

	// Size of the rect that represents the object, specified when constructing the object
	Vector2Int m_size;

	// Rectangle representing orientation and size.
	SDL_Rect m_rect;

public:
	// The position of the object.
	Vector2 m_position;

	/// <summary>
	/// Spawns a new object.
	/// </summary>
	/// <param name="size"></param>
	/// <param name="position"></param>
	/// <param name="rotation"></param>
	GameObject(const Vector2 position = VEC2_ZERO, const float rotation = 0, const Vector2Int size = VEC2INT_DEFAULTSIZE, const bool createCollider = true);
	~GameObject();

	virtual void OnCollision(GameObject* other) {}

	void OnCollisionEnemy(GameObject* other);

	/// <summary>
	/// Will create a new collider on the heap, will not delete the old one. Useful in the object pool when copying memory
	/// </summary>
	void CreateCollider();

	/// <summary>
	/// Returns the object's position.
	/// </summary>
	Vector2 GetPosition() { return m_position; }

	/// <summary>
	/// Sets the object's position.
	/// </summary>
	void SetPosition(Vector2);

	/// <summary>
	/// Sets the object's rotation.
	/// </summary>
	void SetRotation(float);

	/// <summary>
	/// Returns the object's rotation.
	/// </summary>
	float GetRotation() { return m_rotation; }

	/// <summary>
	/// Returns the object's size (the size of the rect).
	/// </summary>
	Vector2Int GetSize() { return m_size; }

	/// <summary>
	/// Sets the object's size (the size of the rect).
	/// </summary>
	void SetSize(Vector2Int);

	/// <summary>
	/// Returns the object's rect
	/// </summary>
	SDL_Rect* GetRect() { return &m_rect; };

	/// <summary>
	/// Should the object be drawn on the screen?
	/// </summary>
	/// <returns></returns>
	bool IsVisible() { return m_isVisible; }

	void SetCollidable(bool state);

	Vector2 m_currentVelocity;

	float m_currentTorque;

	float m_rotationSpeed;

	float m_movementSpeed;

	float m_maxMovementSpeed;

	int m_objectPoolIndex;

	virtual GameObjectID GetID() { return GameObjectID::NONE; }

	virtual void FixedUpdate(float fixedTimeStep, float currentTime);

	virtual void Update(float deltaTime, float currentTime);

	Vector2 forward;
};

