#include "Game.h"
#include <iostream>

void Game::AddObject(GameObject* obj)
{
	m_objects.push_back(obj);
}

Game::~Game()
{
	std::cout << "Deleted game with name: " << m_name << std::endl;

	m_objects.clear();
}

void Game::Update(float deltaTime, float currentTime)
{
	if (m_garbageStack.size() > 0)
		DestroyFlaggedObjects();
}

void Game::FixedUpdate(float fixedTimeStep, float currentTime)
{
	if (m_garbageStack.size() > 0)
	{
		DestroyFlaggedObjects();
	}
}

void Game::RemoveObject(GameObject* obj)
{
	m_garbageStack.push_back(obj);
}

void Game::DestroyFlaggedObjects()
{
	GameObject* obj;
	for (int i = 0; i < m_objects.size(); i++)
	{
		std::cout << &m_objects[i] << std::endl;

		// Search for all objects in the list that are pinned to the
		// garbage stick, and delete them.
		for (int j = 0; j < m_garbageStack.size(); j++)
		{
			if ((obj = m_objects[i]) == m_garbageStack[j])
			{
				m_objects.erase(m_objects.begin() + i);
				m_garbageStack.erase(m_garbageStack.begin() + j);

				delete obj;
			}
		}

		if (m_garbageStack.size() == 0)
			break;
	}

	m_garbageStack.clear();
}

void Game::ClearObjects()
{
	for (int i = 0; i < m_objects.size(); i++)
	{
		delete m_objects[i];
	}

	m_objects.clear();
}