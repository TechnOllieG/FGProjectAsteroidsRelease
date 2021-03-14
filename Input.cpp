#include "Input.h"

void Input::PollKeys(SDL_Event event)
{
    bool state;

    if (event.type == SDL_KEYDOWN)
        state = true;
    else if (event.type == SDL_KEYUP)
        state = false;
    else
        return;

    SDL_Keycode code = event.key.keysym.sym;

    switch (code)
    {
    case SDLK_a:
    {
        m_rotateLeft = state;
        break;
    }
    case SDLK_d:
    {
        m_rotateRight = state;
        break;
    }
    case SDLK_w:
    {
        m_gas = state;
        break;
    }
    case SDLK_SPACE:
    {
        m_shoot = state;
        break;
    }
    }
}