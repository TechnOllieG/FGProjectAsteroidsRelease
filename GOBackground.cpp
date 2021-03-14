#include "GOBackground.h"
#include "GameHandler.h"

GOBackground::GOBackground() : GameObject(GameHandler::GetResolution() * 0.5f, 0, GameHandler::GetResolution(), false) {}

GameObjectID GOBackground::GetID()
{
	return GameObjectID::BACKGROUND;
}