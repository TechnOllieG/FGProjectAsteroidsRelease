#pragma once

#include "GameObject.h"
#include "Assets.h"
#include "Random.h"
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>

class GameHandler;
class Particle;
class ParticleEmissionShape;
struct CircleEmitterShape;
struct RectangleEmitterShape;

//static const ParticleProperties explosionCore = ParticleProperties(ParticleTextureID::EXPLOSION, 1, { 0.8f, 1.2f }, VEC2_ZERO, VEC2_ZERO, VEC2_ZERO, VEC2_ONE * 0.2f, VEC2_ONE, { 0.5f, 0.5f, 64, 64 });
//static const ParticleProperties explosionDebris = ParticleProperties(ParticleTextureID::DEBRIS, 1, { 0.7f, 1.5f }, { -360, 360 }, { 4, 2 }, { 12, 7 }, VEC2_ZERO, VEC2_ONE, { 0.5f, 0.5f, 12, 8 });

enum class ParticleSystemState
{
	PLAYING,
	STOPPED,
	PAUSED
};

//!--ParticleProperties--!//
#pragma region ParticleProperties

struct ParticleProperties
{
	ParticleProperties() {}

	ParticleProperties(ParticleTextureID particleTextureID, float lifetime, Vector2 directionArc, Vector2 speedOverLifetime, Vector2 rotationSpeedOverLifetime, Vector2 imageCycleSpeedOverLifetime, Vector2 sizeOverLifetime, SDL_FRect sizeAndPivot, Vector2 lifetimeVarianceMult = VEC2_ONE, Vector2 speedVarianceMult = VEC2_ONE, Vector2 rotationVarianceMult = VEC2_ONE, Vector2 imageVarianceMult = VEC2_ONE, Vector2 sizeVarianceMult = VEC2_ONE)
	{
		this->particleTextureID = particleTextureID;
		this->lifetime = lifetime;
		this->lifetimeVarianceMultiplier = lifetimeVarianceMult;
		this->directionArc = directionArc;
		this->speedOverLifetime = speedOverLifetime;
		this->rotationSpeedOverLifetime = rotationSpeedOverLifetime;
		this->imageCycleSpeedOverLifetime = imageCycleSpeedOverLifetime;
		this->sizeOverLifetime = sizeOverLifetime;
		this->sizeAndPivot = sizeAndPivot;

		this->speedVarianceMult = speedVarianceMult;
		this->rotationVarianceMult = rotationVarianceMult;
		this->imageCycleVarianceMult = imageVarianceMult;
		this->sizeVarianceMult = sizeVarianceMult;
	}

	ParticleTextureID particleTextureID;

	/// <summary>
	/// For how long should the particle be alive for?
	/// </summary>
	float lifetime;

	/// <summary>
	/// Randomly multiplies the base particle lifetime on spawn.
	/// </summary>
	Vector2 lifetimeVarianceMultiplier;
	float GetLifetimeVariance() { return Random::Range(lifetimeVarianceMultiplier.x, lifetimeVarianceMultiplier.y); }

	/// <summary>
	// The range of angles the particle may move in.
	// X = The lowest direction angle, Y = The highest direction angle.
	/// </summary>
	Vector2 directionArc;
	float GetRandomizedDirection() { return Random::Range(directionArc.x, directionArc.y); }

	/// <summary>
	/// The speed at which the particle moves
	/// in its direction. 
	/// X = The speed at spawn, Y = The speed at destruction.
	/// </summary>
	Vector2 speedOverLifetime;

	Vector2 speedVarianceMult;

	/// <summary>
	/// The speed at which the particle rotates.
	/// X = The speed at spawn, Y = The speed at destruction.
	/// </summary>
	Vector2 rotationSpeedOverLifetime;

	Vector2 rotationVarianceMult;

	/// <summary>
	/// The speed at which the particle cycles
	/// through the image sheet. Frames are cycled through
	/// each integer number.
	/// X = The speed at spawn, Y = The speed at destruction.
	/// </summary>
	Vector2 imageCycleSpeedOverLifetime;

	Vector2 imageCycleVarianceMult;

	/// <summary>
	/// The size multiplier of the particle.
	/// X = The size at spawn, Y = The size at destruction.
	/// </summary>
	Vector2 sizeOverLifetime;

	Vector2 sizeVarianceMult;

	/// <summary>
	/// The rect defining the particle's pixel size and
	/// pivot point. Keep in mind that the pivot point is
	/// normalized!
	/// </summary>
	SDL_FRect sizeAndPivot;

	static float EvaluateOverLifetime(const Vector2 overLifetime, float normalizedTime) { return overLifetime.x + (overLifetime.y - overLifetime.x) * std::max<float>(0, std::min<float>(normalizedTime, 1)); }
};



/// <summary>
/// Wrapper that tells the particle system how many
/// particles to spawn with this property.
/// </summary>
struct ParticleSpawnWrapper
{
	//ParticleSpawnWrapper(int count, ParticleProperties properties)
	//{
	//	this->count = count;
	//	this->properties = properties;
	//}

	int count;
	ParticleProperties properties;
};

#pragma endregion

class GOParticleSystem : public GameObject
{
public:
	GOParticleSystem(std::vector<ParticleSpawnWrapper> particles, CircleEmitterShape circleShape, const float duration, const bool loop, const bool particlesDieWithSystem, const bool particlesAreInLocalSpace, const Vector2 position = VEC2_ZERO, const float rotation = 0, const Vector2Int size = VEC2INT_DEFAULTSIZE);
	GOParticleSystem(std::vector<ParticleSpawnWrapper> particles, RectangleEmitterShape rectShape, const float duration, const bool loop, const bool particlesDieWithSystem, const bool particlesAreInLocalSpace, const Vector2 position = VEC2_ZERO, const float rotation = 0, const Vector2Int size = VEC2INT_DEFAULTSIZE);
	~GOParticleSystem();

	void Update(float deltaTime, float currentTime);

	void FixedUpdate(float fixedTimeStep, float currentTime);

	void Play();
	// Stops the processing of the particle system,
	// but keeps rendering.
	void Pause();
	// Deactivates everything.
	void Stop();

	GameObjectID GetID();

private:
	std::vector<Particle*> m_particles;

	std::vector<Particle*> m_activeParticles;

	std::vector<ParticleProperties> m_properties;

	ParticleEmissionShape* m_emission;

	bool m_loop;

	// Should all remaining active particles deactivate
	// when the particle system does?
	bool m_particlesDieWithSystem;

	// Should all particles move with the system, or should
	// they be independent?
	bool m_particlesAreInLocalSpace;

	float m_duration;



	ParticleSystemState state;

public:
	ParticleSystemState GetState() const { return state; }
};
