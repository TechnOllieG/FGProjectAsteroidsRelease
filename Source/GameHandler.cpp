#include "GameHandler.h"
#include <iostream>

SDL_Renderer* GameHandler::m_renderer = nullptr;
Vector2 GameHandler::m_screenResolution = Vector2(800, 600);
bool GameHandler::m_resetFlag = false;
float GameHandler::m_currentTime = 0;
Game* GameHandler::m_game = nullptr;

GameHandler::GameHandler()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    m_applicationRunning = true;

    m_game = new AsteroidsGame(m_screenResolution);

    m_window = SDL_CreateWindow(m_game->m_name.c_str(), SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, m_screenResolution.x, m_screenResolution.y, SDL_WINDOW_SHOWN);

    m_renderer = SDL_CreateRenderer(m_window, -1, 0);
}

GameHandler::~GameHandler()
{
    delete m_game;

    SDL_DestroyRenderer(m_renderer);

    SDL_DestroyWindow(m_window);

    SDL_Quit();
}

void GameHandler::ResetGame()
{
    m_resetFlag = true;
}

void GameHandler::GameReset()
{
    delete m_game;
    m_game = new AsteroidsGame(m_screenResolution);
    Start();
    m_resetFlag = false;
}

void GameHandler::GameLoop()
{
    GameHandler::Start();

    while (m_applicationRunning)
    {
        ClearScreen();

        float tempTime = SDL_GetTicks() * 0.001;
        m_deltaTime = tempTime - m_currentTime;
        m_currentTime = tempTime;

        m_accumulator += m_deltaTime;

        while (m_accumulator >= m_fixedTimeStep)
        {
            FixedUpdate();
            m_accumulator -= m_fixedTimeStep;
        }

        while (SDL_PollEvent(&m_evt))
        {
            if (m_evt.type == SDL_QUIT)
                m_applicationRunning = false;

            HandleInput();
        }

        Update();

        DrawUpdate();
        SDL_RenderPresent(m_renderer);
    }
}

void GameHandler::Start()
{
    std::cout << "Game Start" << std::endl;
    m_game->Start();
}

void GameHandler::HandleInput()
{
    m_game->HandleInput(m_evt);
}

void GameHandler::Update()
{
    m_game->Update(m_deltaTime, m_currentTime);

    if (m_resetFlag)
        GameReset();
}

void GameHandler::FixedUpdate()
{
    m_game->FixedUpdate(m_fixedTimeStep, m_currentTime);
}

void GameHandler::DrawUpdate()
{
    m_game->DrawGraphics(m_renderer);
}

void GameHandler::ClearScreen()
{
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
}