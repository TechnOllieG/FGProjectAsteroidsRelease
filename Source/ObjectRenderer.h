#pragma once
#include <map>
#include <string>

class ObjectRenderer
{
public:
	~ObjectRenderer();
	void Render(SDL_Renderer* renderer, std::vector<GameObject*> objects);
	void Render(SDL_Renderer* renderer, GameObject* obj);
	void Init();

private:
	std::map<GameObjectID, SDL_Texture*> m_objectTextureMap;
};