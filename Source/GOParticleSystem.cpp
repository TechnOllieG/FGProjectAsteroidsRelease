#include "GOParticleSystem.h"
#include "Particle.h"
#include "ParticleEmissionShape.h"
#include "GameHandler.h"

#include <iostream>

GOParticleSystem::GOParticleSystem(std::vector<ParticleSpawnWrapper> particles, CircleEmitterShape circleShape, const float duration, const bool loop, const bool particlesDieWithSystem, const bool particlesAreInLocalSpace, const Vector2 position, const float rotation, const Vector2Int size) : GameObject(position, rotation, size, false)
{
	m_properties.resize(particles.size());

	for (int i = 0; i < particles.size(); i++)
	{
		//ParticleProperties* prop = (ParticleProperties*)malloc(sizeof(ParticleProperties));



		//memcpy(m_properties[i], particles[i].properties, sizeof(ParticleProperties));
		m_properties[i] = particles[i].properties;

		std::cout << "sizeVarianceMult " << m_properties[i].sizeVarianceMult.x << std::endl;
		std::cout << "particles = " << particles[i].properties.sizeVarianceMult.x << std::endl;

		//m_properties.push_back(*prop);

		for (int j = 0; j < particles[i].count; j++)
		{
			Particle* part = new Particle(&m_properties[i], &m_position);

			m_particles.push_back(part);
		}
	}

	m_emission = new CircleEmitter(circleShape.radius, circleShape.innerRadius);

	m_loop = loop;
	m_particlesDieWithSystem = particlesDieWithSystem;
	m_duration = duration;
	m_particlesAreInLocalSpace = particlesAreInLocalSpace;
	state = ParticleSystemState::STOPPED;
}

GOParticleSystem::GOParticleSystem(std::vector<ParticleSpawnWrapper> particles, RectangleEmitterShape rectShape, const float duration, const bool loop, const bool particlesDieWithSystem, const bool particlesAreInLocalSpace, const Vector2 position, const float rotation, const Vector2Int size) : GameObject(position, rotation, size, false)
{
	m_properties.resize(particles.size());

	for (int i = 0; i < particles.size(); i++)
	{
		ParticleProperties* prop = (ParticleProperties*)malloc(sizeof(ParticleProperties));

		std::cout << "i = " << i << std::endl;
		std::cout << "mProps size = " << m_properties.size() << std::endl;

		memcpy(&m_properties[i], &particles[i].properties, sizeof(ParticleProperties));


		//m_properties.push_back(*prop);

		for (int j = 0; j < particles[i].count; j++)
		{
			Particle* part = new Particle(prop, &m_position);

			m_particles.push_back(part);
		}
	}

	m_emission = new RectangleEmitter(rectShape.rect);

	m_loop = loop;
	m_particlesDieWithSystem = particlesDieWithSystem;
	m_duration = duration;
	m_particlesAreInLocalSpace = particlesAreInLocalSpace;
	state = ParticleSystemState::STOPPED;
}

GOParticleSystem::~GOParticleSystem()
{
	//for (ParticleProperties prop : m_properties)
	//{
	//	delete &prop;
	//}

	for (Particle* part : m_particles)
	{
		delete part;
	}

	delete m_emission;
}

void GOParticleSystem::FixedUpdate(float fixedTimeStep, float currentTime)
{
	if (state != ParticleSystemState::STOPPED)
	{
		int size = m_activeParticles.size();

		for (int i = 0; i < size; i++)
		{
			if (state == ParticleSystemState::PLAYING &&
				!m_activeParticles[i]->OnParticleSystemUpdate(fixedTimeStep, currentTime))
			{
				if (!m_loop)
				{
					//m_activeParticles[i]->active = false;
					m_activeParticles.erase(m_activeParticles.begin() + i);
					size--;
					continue;
				}
				else
				{
					m_activeParticles[i]->OnStart(m_emission->GetRandomPosition(VEC2_ZERO), currentTime);
				}
			}
		}

		if (size <= 0)
			Stop();
	}
}

void GOParticleSystem::Play()
{
	if (state != ParticleSystemState::STOPPED)
	{
		Stop();
	}

	m_activeParticles.clear();

	Vector2 spawnPos;

	for (Particle* p : m_particles)
	{
		spawnPos = m_emission->GetRandomPosition(VEC2_ZERO);
		p->OnStart(spawnPos, GameHandler::GetTime());

		m_activeParticles.push_back(p);
	}

	state = ParticleSystemState::PLAYING;
}

void GOParticleSystem::Pause()
{
	state = ParticleSystemState::PAUSED;
}

void GOParticleSystem::Stop()
{
	for (int i = 0; i < m_activeParticles.size(); i++)
	{
		m_activeParticles[i]->OnStop();
	}

	m_activeParticles.clear();

	state = ParticleSystemState::STOPPED;
}

void GOParticleSystem::Update(float deltaTime, float currentTime)
{
	//std::cout << m_activeParticles.size() << std::endl;

	for (int i = 0; i < m_activeParticles.size(); i++)
	{
		m_activeParticles[i]->OnRender();
	}
}

GameObjectID GOParticleSystem::GetID()
{
	return GameObjectID::PARTICLESYSTEM;
}