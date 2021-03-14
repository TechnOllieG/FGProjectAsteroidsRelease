#pragma once
#include <vector>
#include <iostream>
#include "GameObject.h"
#include "GOAsteroid.h"
#include "GOShot.h"
#include "Library.h"
#include "Collider.h"

template <typename T>
struct Object
{
	Object(T* object)
	{
		obj = object;
	}

	T* obj;
	bool currentlyUsed = false;
};

template<typename T>
class ObjectPool
{
private:
	std::vector<Object<T>> objects;

public:
	/// <summary>
	/// Deallocates all objects in the pool from the heap (any pointers recieved from GetObject will be invalidated)
	/// </summary>
	void Clear()
	{
		for (int i = 0; i < objects.size(); i++)
		{
			delete objects[i].obj;
		}

		objects.clear();
	}

	/// <summary>
	/// Fills the internal vector container with the specified amount of items (will be copies of the templateItem)
	/// </summary>
	/// <param name="amountOfItemsToPool">The amount of items contained in the pool</param>
	/// <param name="templateItem">The instance of what will be allocated in the object pool</param>
	void Allocate(const int amountOfItemsToPool, T templateItem)
	{
		objects.reserve(amountOfItemsToPool);

		for (int i = 0; i < amountOfItemsToPool; i++)
		{
			T* heapPointer = (T*) malloc(sizeof(T));
			if (heapPointer == nullptr)
			{
				std::cout << "Failed to allocate memory for object pool of type" << typeid(T).name() << std::endl;
				return;
			}
			memcpy(heapPointer, &templateItem, sizeof(T));

			heapPointer->CreateCollider();
			heapPointer->SetCollidable(false);

			objects.push_back(Object<T>(heapPointer));
		}
	}

	~ObjectPool()
	{
		Clear();
	}

	T* GetObject(int* objectPoolIndex)
	{
		for (int i = 0; i < objects.size(); i++)
		{
			if (!objects[i].currentlyUsed)
			{
				objects[i].currentlyUsed = true;
				*objectPoolIndex = i;
				return objects[i].obj;
			}
		}
	}

	void ReturnObject(const int objectPoolIndex)
	{
		objects[objectPoolIndex].currentlyUsed = false;
	}
};