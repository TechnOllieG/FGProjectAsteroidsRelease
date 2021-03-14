#pragma once
#include <map>
#include <iostream>
#include <typeinfo>
#include "Library.h"
#include "AsteroidsGame.h"
#include "State.h"

class AsteroidsGame;

class StateMachine
{
public:
	StateMachine(AsteroidsGame* user, AsteroidGameState* entryState);
	~StateMachine();

	/// <summary>
	/// Changes the state being processed by the state machine.
	/// </summary>
	/// <param name="newState">The type of state to </param>
	void ChangeState(AsteroidGameState* newState);

	void Update(float deltaTime, float currentTime);
	void FixedUpdate(float fixedTimeStep, float currentTime);
	void DrawGraphics(SDL_Renderer* renderer);

	AsteroidsGame* m_user = nullptr;

protected:
	//std::map<std::type_info, State*> m_states;
	AsteroidGameState* m_previous = nullptr;
	AsteroidGameState* m_current = nullptr;
};

