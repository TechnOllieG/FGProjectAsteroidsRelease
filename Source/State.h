#pragma once

class StateMachine;
class AsteroidsGame;

/// <summary>
/// Base class for the game's different states.
/// </summary>
class AsteroidGameState
{
public:
	virtual void StateEnter(StateMachine* stateMachine, AsteroidGameState* previous) {}
	virtual void StateUpdate(float deltaTime, float currentTime) {}
	virtual void StateFixedUpdate(float fixedTimeStep, float currentTime) {}
	virtual void StateDrawGraphics(SDL_Renderer* renderer) {}
	virtual void StateExit(AsteroidGameState* next) {}

protected:
	AsteroidsGame* m_user;
	StateMachine* m_machine = nullptr;
};