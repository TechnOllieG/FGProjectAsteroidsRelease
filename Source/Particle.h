#pragma once

#include "GOParticleSystem.h"
//#include "GameHandler.h"

class Particle
{
public:
	Particle(ParticleProperties* properties, Vector2* particleSystemOrigin);
	~Particle();



	// The point which localPosition should be relative to.
	Vector2* origin;

	ParticleProperties* properties;

	//Vector2Int cellSize;
	//uint32_t cellCount;

	void OnStart(Vector2 spawnOrigin, const float currentTime);

	void OnStop();

	bool OnParticleSystemUpdate(float fixedTimeStep, float currentTime);

	void OnRender();

private:
	static std::map<ParticleTextureID, SDL_Texture*> m_texCache;

	SDL_Texture* m_textureSheet;

	//--Current values--//
	float m_timeSpawnedAt;

	float m_lifetime;
	float m_currentAge;

	float m_v_speed;
	float m_v_speedMult;

	float m_v_direction;

	// Where the particle was spawned.
	Vector2 m_p_localPosition;

	SDL_FRect m_r_rect;

	float m_rotation;
	float m_rotationMult;

	float m_imageIndex;
	float m_imgSpeedMult;

	float m_sizeScale;
	float m_sizeMult;

	bool m_active;

	SDL_Texture* AssignTexture(const ParticleTextureID ptexID);
};