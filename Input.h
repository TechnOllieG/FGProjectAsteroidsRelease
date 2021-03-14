#pragma once
#include "SDL.h"
#include "Library.h"

struct Input
{
public:
	void PollKeys(SDL_Event event);
	bool m_rotateLeft = false;
	bool m_rotateRight = false;
	bool m_gas = false;
	bool m_shoot = false;
};