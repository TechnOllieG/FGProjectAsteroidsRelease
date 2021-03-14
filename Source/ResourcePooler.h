#pragma once

#include <vector>
#include <map>
#include "GameObject.h"

class ResourcePooler
{

public:
	// Map that contains lists over objects of all types.
	std::map<GameObjectID, std::vector<GameObject>> objectPool;

	std::map<GameObjectID, std::vector<GameObject>> persistentPool;

};