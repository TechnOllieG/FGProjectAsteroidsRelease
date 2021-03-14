#include "GOUIImage.h"

GOUIImage::GOUIImage(Vector2 position, float rotation, Vector2Int size, GameObjectID textureID) : GameObject(position, rotation, size, false)
{
	m_textureID = textureID;
}

void GOUIImage::ChangeTexture(GameObjectID texture)
{
	m_textureID = texture;
}

GameObjectID GOUIImage::GetID()
{
	return m_textureID;
}