#include "Random.h"
#include "AsteroidsGame.h"
#include "GOAsteroid.h"
#include "GOPlayer.h"
#include "GOUIImage.h"
#include "GameHandler.h"
#include "SymbolDisplay.h"
#include <iostream>
#include <fstream>
#include <string>

// ---------------------- AsteroidsGame Logic ----------------------
#pragma region AsteroidsGame
std::vector<GameObject*> AsteroidsGame::m_garbageStack;
std::vector<GameObject*> AsteroidsGame::m_objects;
int AsteroidsGame::m_points = 0;
int AsteroidsGame::m_lives = 3;
float AsteroidsGame::m_timeOfDeath = 0;

GOPlayer* AsteroidsGame::m_player = nullptr;
StateMachine* AsteroidsGame::m_gameStateMachine = nullptr;
std::map<GameStateMap, AsteroidGameState*> AsteroidsGame::m_gameStates = std::map<GameStateMap, AsteroidGameState*>();

ObjectPool<GOAsteroid> AsteroidsGame::m_asteroidPool = ObjectPool<GOAsteroid>();
ObjectPool<GOShot> AsteroidsGame::m_shotPool = ObjectPool<GOShot>();
ObjectPool<GOUfo> AsteroidsGame::m_ufoPool = ObjectPool<GOUfo>();

AsteroidsGame::AsteroidsGame(Vector2 screenResolution)
{
	Random::SRand();

	m_name = "Asteroids";
	m_lives = 3;
	m_timeOfDeath = 0;

	std::ifstream myfile = std::ifstream("score.dat");
	if (myfile.is_open())
	{
		myfile >> m_highScore;
		myfile.close();
	}

	AddPlayer(screenResolution);

	GOShot shotTemplate = GOShot(VEC2_ZERO, 0, Vector2Int(20, 20), VEC2_ZERO, false);
	GOAsteroid asteroidTemplate = GOAsteroid(VEC2_ZERO, 0, Vector2Int(40, 40), VEC2_ZERO, 0, false);
	GOUfo ufoTemplate = GOUfo(VEC2_ZERO, 0, Vector2Int(40, 40), m_player, false);

	m_shotPool.Allocate(20, shotTemplate);
	m_asteroidPool.Allocate(20, asteroidTemplate);
	m_ufoPool.Allocate(20, ufoTemplate);

	m_gameStates[GameStateMap::INIT] = new AGS_Init(&m_renderer);
	m_gameStates[GameStateMap::GAME] = new AGS_Game(&m_spawner, &m_renderer, &m_points, &m_objects);
	m_gameStates[GameStateMap::GAMEOVER] = new AGS_GameOver(&m_points, &m_renderer);
}

AsteroidsGame::~AsteroidsGame()
{
	m_player = nullptr;

	m_points = 0;
	
	m_asteroidPool.Clear();
	m_shotPool.Clear();
	m_ufoPool.Clear();

	for (int i = 0; i < 4; i++)
	{
		delete m_objects[0];
		m_objects.erase(m_objects.begin());
	}

	delete m_gameStateMachine;
	
	for (std::pair<GameStateMap, AsteroidGameState*> state : m_gameStates)
	{
		delete state.second;
	}

	m_gameStates.clear();
}

void AsteroidsGame::OnGameOver()
{
	AudioManager::StopLoopedSound(AudioID::GAS, 250);
	m_gameStateMachine->ChangeState(GetGameState(GameStateMap::GAMEOVER));
}

void AsteroidsGame::AddPlayer(Vector2 screenResolution)
{
	m_player = new GOPlayer(screenResolution * 0.5f, 0.0f, Vector2Int(40, 40), &m_input);
	m_player->SetCollidable(true);
	AddObject(m_player);
}

void* AsteroidsGame::GetObject(GameObjectID id)
{
	void* obj;
	int objPoolIndex;

	switch (id)
	{
	case GameObjectID::ASTEROID:
		obj = m_asteroidPool.GetObject(&objPoolIndex);
		((GOAsteroid*)obj)->m_objectPoolIndex = objPoolIndex;
		break;
	case GameObjectID::SHOT:
		obj = m_shotPool.GetObject(&objPoolIndex);
		((GOShot*)obj)->m_objectPoolIndex = objPoolIndex;
		break;
	case GameObjectID::UFO:
		obj = m_ufoPool.GetObject(&objPoolIndex);
		((GOUfo*)obj)->m_objectPoolIndex = objPoolIndex;
		break;
	default:
		std::cout << "The specified type does not have an object pool" << std::endl;
		return nullptr;
		break;
	}

	if (obj == nullptr)
	{
		std::cout << "Couldn't get object from pool, maybe all objects are used up?" << std::endl;
		return nullptr;
	}

	return obj;
}

void AsteroidsGame::LooseLife()
{
	((GOUIImage*)m_objects[m_lives])->ChangeTexture(GameObjectID::UILOSTLIFE);
	m_lives--;

	m_player->SetPosition(GameHandler::GetResolution() * 0.5f);
	m_player->m_currentVelocity = VEC2_ZERO;
	m_player->m_currentTorque = 0;
	m_timeOfDeath = GameHandler::GetTime();
}

bool AsteroidsGame::IsPlayerInvulnerable()
{
	return GameHandler::GetTime() - m_timeOfDeath < 1.5f;
}

int AsteroidsGame::GetLives()
{
	return m_lives;
}

void AsteroidsGame::ReturnObject(GameObject* obj)
{
	switch (obj->GetID())
	{
	case GameObjectID::ASTEROID:
		m_asteroidPool.ReturnObject(obj->m_objectPoolIndex);
		break;
	case GameObjectID::SHOT:
		m_shotPool.ReturnObject(obj->m_objectPoolIndex);
		break;
	case GameObjectID::UFO:
		m_ufoPool.ReturnObject(obj->m_objectPoolIndex);
		break;
	default:
		std::cout << "The specified type does not have an object pool" << std::endl;
		return;
	}

	for (int i = 0; i < m_objects.size(); i++)
	{
		if(m_objects[i] == obj)
			m_objects.erase(m_objects.begin() + i);
	}
}

void AsteroidsGame::Start() 
{
	m_gameStateMachine = new StateMachine(this, GetGameState(GameStateMap::INIT));
}

void AsteroidsGame::HandleInput(SDL_Event event) { m_input.PollKeys(event); }

void AsteroidsGame::Update(float deltaTime, float currentTime) { m_gameStateMachine->Update(deltaTime, currentTime); }

void AsteroidsGame::FixedUpdate(float fixedTimeStep, float currentTime) { m_gameStateMachine->FixedUpdate(fixedTimeStep, currentTime); }

void AsteroidsGame::DrawGraphics(SDL_Renderer* renderer) { m_gameStateMachine->DrawGraphics(renderer); }
#pragma endregion

// ---------------------- Asteroid Game State: Init ----------------------
#pragma region AGS_Init
void AGS_Init::StateEnter(StateMachine* stateMachine, AsteroidGameState* previous)
{
	m_machine = stateMachine;
	m_user = m_machine->m_user;

	Vector2 resolution = GameHandler::GetResolution();

	m_user->AddObject(new GOUIImage(Vector2(resolution.x - m_lifeUISize * 0.5f - m_lifeUIMargin, 25), 0, Vector2Int(m_lifeUISize, m_lifeUISize), GameObjectID::UILIFE));
	m_user->AddObject(new GOUIImage(Vector2(resolution.x - m_lifeUISize * 1.5f - m_lifeUIMargin * 2, 25), 0, Vector2Int(m_lifeUISize, m_lifeUISize), GameObjectID::UILIFE));
	m_user->AddObject(new GOUIImage(Vector2(resolution.x - m_lifeUISize * 2.5f - m_lifeUIMargin * 3, 25), 0, Vector2Int(m_lifeUISize, m_lifeUISize), GameObjectID::UILIFE));

	m_renderer->Init();

	m_machine->ChangeState(m_user->GetGameState(GameStateMap::GAME));
}
#pragma endregion

// ---------------------- Asteroid Game State: Game ----------------------
#pragma region AGS_Game
void AGS_Game::StateEnter(StateMachine* stateMachine, AsteroidGameState* previous)
{
	m_resolution = GameHandler::GetResolution();
	m_machine = stateMachine;
	m_user = m_machine->m_user;
}

void AGS_Game::StateUpdate(float deltaTime, float currentTime)
{
	m_renderer->Render(GameHandler::GetRenderer(), &m_background);

	for (int i = 0; i < m_objects->size(); i++)
	{
		if (m_stopRunning)
			break;

		(*m_objects)[i]->Update(deltaTime, currentTime);
	}

	m_user->Game::Update(deltaTime, currentTime);
}

void AGS_Game::StateFixedUpdate(float fixedTimeStep, float currentTime)
{
	m_spawner->TrySpawn(currentTime);

	for (int i = 0; i < m_objects->size(); i++)
	{
		if (m_stopRunning)
			break;

		(*m_objects)[i]->FixedUpdate(fixedTimeStep, currentTime);
	}

	m_user->Game::FixedUpdate(fixedTimeStep, currentTime);
}

void AGS_Game::StateDrawGraphics(SDL_Renderer* renderer)
{
	// Render objects
	m_renderer->Render(renderer, *m_objects);

	// Render score counter on top left of screen
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	std::vector<SymbolDisplay> scoreSymbols = SymbolDisplay::GetSymbols("score:" + std::to_string(*m_points), 
		m_symbolPixelScale, Vector2Int(m_pointCounterMargin, m_pointCounterMargin));

	for (SymbolDisplay sym : scoreSymbols)
		sym.Draw(renderer);

	std::vector<SymbolDisplay> highScoreSymbols = SymbolDisplay::GetSymbols("high score:" + std::to_string(m_user->m_highScore), m_symbolPixelScale, 
		Vector2Int(m_pointCounterMargin, m_resolution.y - (m_pointCounterMargin + 5 * m_symbolPixelScale)));

	for (SymbolDisplay sym : highScoreSymbols)
		sym.Draw(renderer);
}

void AGS_Game::StateExit(AsteroidGameState* next)
{
	m_stopRunning = true;
}
#pragma endregion

// ---------------------- Asteroid Game State: GameOver ----------------------
#pragma region AGS_GameOver
void AGS_GameOver::StateEnter(StateMachine* stateMachine, AsteroidGameState* previous)
{
	m_resolution = GameHandler::GetResolution();

	m_machine = stateMachine;
	m_user = m_machine->m_user;

	std::ifstream scoreFileRead;
	scoreFileRead.open("score.dat");
	int current = 0;

	if (scoreFileRead.is_open())
	{
		std::cout << "Score file exists already" << std::endl;
		scoreFileRead >> current;

		scoreFileRead.close();
	}

	if (current < *m_points)
	{
		std::cout << "New high score!" << std::endl;
		m_newHighScore = true;
		m_user->m_highScore = *m_points;
		std::ofstream scoreFileWrite;
		scoreFileWrite.open("score.dat");
		if (scoreFileWrite.is_open())
		{
			scoreFileWrite << *m_points;
			scoreFileWrite.close();
		}
	}
	else
		std::cout << "Old high score is higher" << std::endl;

	int retryTextWidth = (3 * 5 + 4) * m_symbolPixelScale; // 3 for pixelWidth of one letter, 5 for 5 letters in retry, 4 for 4 spaces (1 pixel per space)

	m_retryButtonRect = SDL_Rect
	{
		(int)((m_resolution.x - retryTextWidth) * 0.5f) - m_retryButtonTextMargin,
		m_retryButtonTopOffset,
		retryTextWidth + m_retryButtonTextMargin * 2,
		5 * m_symbolPixelScale + m_retryButtonTextMargin * 2
	};
}

void AGS_GameOver::StateUpdate(float deltaTime, float currentTime)
{
	Vector2Int mousePos;
	SDL_PumpEvents();
	if (SDL_GetMouseState(&mousePos.x, &mousePos.y) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		if (Library::IsInRect(mousePos, m_retryButtonRect))
			m_holdingRetryButton = true;
		else
			m_holdingRetryButton = false;
	}
	else
	{
		if (Library::IsInRect(mousePos, m_retryButtonRect) && m_holdingRetryButton)
		{
			GameHandler::ResetGame();
		}
	}
}

void AGS_GameOver::StateFixedUpdate(float fixedTimeStep, float currentTime)
{

}

void AGS_GameOver::StateDrawGraphics(SDL_Renderer* renderer)
{
	m_renderer->Render(renderer, m_background);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	
	if (m_holdingRetryButton)
		SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);

	// Render retry button
	SDL_RenderDrawRect(renderer, &m_retryButtonRect);
	std::vector<SymbolDisplay> retrySymbols = SymbolDisplay::GetSymbolsCentered("retry", m_resolution, m_symbolPixelScale, m_retryButtonTopOffset + m_retryButtonTextMargin);
	for (SymbolDisplay sym : retrySymbols)
		sym.Draw(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	// Render game over text
	std::vector<SymbolDisplay> gameOverSymbols = SymbolDisplay::GetSymbolsCentered("game over", m_resolution, m_gameOverPixelScale, m_gameOverScreenTopOffset);
	for (SymbolDisplay sym : gameOverSymbols)
		sym.Draw(renderer);

	// Render new high score text if a new high score was set
	if (m_newHighScore)
	{
		std::vector<SymbolDisplay> newHighScoreSymbols = SymbolDisplay::GetSymbolsCentered("new high score!", m_resolution, m_gameOverPixelScale, m_gameOverScreenTopOffset * 0.5f);
		for (SymbolDisplay sym : newHighScoreSymbols)
			sym.Draw(renderer);
	}

	// Render score counter in top left corner of screen
	std::vector<SymbolDisplay> scoreSymbols = SymbolDisplay::GetSymbols("score:" + std::to_string(*m_points), m_symbolPixelScale, 
		Vector2Int(m_pointCounterMargin, m_pointCounterMargin));

	for (SymbolDisplay sym : scoreSymbols)
		sym.Draw(renderer);

	// Render high score counter in bottom left corner of screen
	std::vector<SymbolDisplay> highScoreSymbols = SymbolDisplay::GetSymbols("high score:" + std::to_string(m_user->m_highScore), m_symbolPixelScale, 
		Vector2Int(m_pointCounterMargin, m_resolution.y - (m_pointCounterMargin + 5 * m_symbolPixelScale)));

	for (SymbolDisplay sym : highScoreSymbols)
		sym.Draw(renderer);
}

void AGS_GameOver::StateExit(AsteroidGameState* next)
{

}
#pragma endregion
