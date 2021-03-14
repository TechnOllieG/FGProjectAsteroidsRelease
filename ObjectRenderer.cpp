#include <string>
#include <typeinfo>
#include <vector>
#include "Library.h"
#include "GameObject.h"
#include "ObjectRenderer.h"
#include "Assets.h"
#include "GameHandler.h"
#include <iostream>

void ObjectRenderer::Init()
{
	std::cout << "Initialized Object Renderer" << std::endl;

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		std::cout << "Failed to initialize SDL_image, error is: " << SDL_GetError() << std::endl;

	for (const Texture current : textures)
	{
		SDL_Surface* surf = IMG_Load(current.path);
		if (surf == NULL)
			std::cout << "Image loading error, is the path correct?" << std::endl;

		SDL_Texture* texture = SDL_CreateTextureFromSurface(GameHandler::GetRenderer(), surf);

		if (texture == NULL)
			std::cout << "Couldn't convert surface (created from IMG_Load) to SDL_Texture, error is: " << SDL_GetError() << std::endl;

		m_objectTextureMap[current.gameObjectId] = texture;
		SDL_FreeSurface(surf);
	}
}

ObjectRenderer::~ObjectRenderer()
{
	std::cout << "Destroyed Object Renderer" << std::endl;
	IMG_Quit();
	for (std::pair<GameObjectID, SDL_Texture*> surf : m_objectTextureMap)
	{
		SDL_DestroyTexture(surf.second);
	}
}

void ObjectRenderer::Render(SDL_Renderer* renderer, std::vector<GameObject*> objects)
{
	for (GameObject* obj : objects)
	{
		Render(renderer, obj);
	}
}

void ObjectRenderer::Render(SDL_Renderer* renderer, GameObject* obj)
{
	// If the object is a particle system, return since it has it's own rendering logic
	if (obj->GetID() == GameObjectID::PARTICLESYSTEM)
		return;

	SDL_Texture* texture = m_objectTextureMap[obj->GetID()];
	if (texture == nullptr)
		std::cout << SDL_GetError() << std::endl;

	SDL_RenderCopyEx(renderer, texture, NULL, obj->GetRect(), obj->GetRotation(), NULL, SDL_FLIP_NONE);
}