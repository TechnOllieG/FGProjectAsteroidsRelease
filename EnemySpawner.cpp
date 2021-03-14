#include "EnemySpawner.h"
#include "Library.h"
#include "AsteroidsGame.h"
#include "GOAsteroid.h"
#include "GameHandler.h"
#include <tgmath.h>

#define BottomLeftCorner Vector2(0, resolution.y)
#define BottomRightCorner Vector2(resolution.x, resolution.y)
#define TopLeftCorner Vector2(0, 0)
#define TopRightCorner Vector2(resolution.x, 0)

void EnemySpawner::TrySpawn(float currentTime)
{
	if (currentTime - m_timeOfLastSpawn > m_currentSpawnCooldown)
	{
		for (int i = 0; i < sizeof(m_enemyTypes) / sizeof(*m_enemyTypes); i++)
		{
			if (RAND01 > m_enemyTypes[i].spawningRate)
				continue;

			GameObjectID typeToSpawn = m_enemyTypes[i].id;
			Spawn(typeToSpawn);
			m_timeOfLastSpawn = currentTime;
			m_currentSpawnCooldown = Library::Lerp(m_minSpawnCooldown, m_maxSpawnCooldown, RAND01);
		}
	}
}

void EnemySpawner::Spawn(GameObjectID id)
{
	const Vector2Int resolution = GameHandler::GetResolution();
	Vector2 position;
	Vector2 minVector, maxVector;
	const int size = 40;

	int halfSize = size * 0.5f;
	float randSide = RAND01;

	// Spawn left of screen
	if (randSide < 0.25f)
	{
		position.x = -halfSize;
		position.y = resolution.y * RAND01;

		minVector = TopRightCorner - position;
		maxVector = BottomRightCorner - position;
	}
	// Spawn right of screen
	else if (randSide < 0.5f)
	{
		position.x = resolution.x + halfSize;
		position.y = resolution.y * RAND01;

		minVector = TopLeftCorner - position;
		maxVector = BottomLeftCorner - position;
	}
	// Spawn top of screen
	else if (randSide < 0.75f)
	{
		position.y = -halfSize;
		position.x = resolution.x * RAND01;

		minVector = BottomLeftCorner - position;
		maxVector = BottomRightCorner - position;
	}
	// Spawn bottom of screen
	else
	{
		position.y = resolution.y + halfSize;
		position.x = resolution.x * RAND01;

		minVector = TopLeftCorner - position;
		maxVector = TopRightCorner - position;
	}

	switch (id)
	{
	case GameObjectID::ASTEROID:
	{
		const float maxRotSpeed = 5.0f;

		const float minVelSpeed = 1.0f;
		const float maxVelSpeed = 3.0f;

		Vector2 velocity;
		float torque;

		velocity = Library::Lerp(minVector, maxVector, RAND01).normalized() * Library::Lerp(minVelSpeed, maxVelSpeed, RAND01);
		torque = Library::Lerp(-maxRotSpeed, maxRotSpeed, RAND01);

		// AsteroidsGame::AddObject(new GOAsteroid(position, 0, Vector2Int(size, size), velocity, torque));
		GOAsteroid* asteroid = (GOAsteroid*) AsteroidsGame::GetObject(GameObjectID::ASTEROID);

		asteroid->SetPosition(position);
		asteroid->SetRotation(0);
		asteroid->SetSize(Vector2Int(size, size));
		asteroid->m_currentVelocity = velocity;
		asteroid->m_currentTorque = torque;

		AsteroidsGame::AddObject(asteroid);
		break;
	}
	case GameObjectID::UFO:
	{
		std::cout << "Spawned UFO" << std::endl;

		GOUfo* ufo = (GOUfo*)AsteroidsGame::GetObject(GameObjectID::UFO);

		ufo->SetPosition(position);
		ufo->SetRotation(0);
		ufo->SetSize(Vector2Int(size, size));

		AsteroidsGame::AddObject(ufo);
		break;
	}
	}
}