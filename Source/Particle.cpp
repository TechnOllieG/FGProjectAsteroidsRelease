#include "Particle.h"
#include "GameHandler.h"

#include <iostream>

std::map<ParticleTextureID, SDL_Texture*> Particle::m_texCache = {};

Particle::Particle(ParticleProperties* properties, Vector2* particleSystemOrigin)
{
	this->properties = properties;

	m_timeSpawnedAt = 0;

	origin = particleSystemOrigin;

	m_lifetime = properties->lifetime;
	m_v_speed = properties->speedOverLifetime.x;
	m_v_direction = 0;
	m_p_localPosition = { 0, 0 };

	m_r_rect = properties->sizeAndPivot;

	m_rotation = 0;


	m_imageIndex = 0;

	m_sizeScale = 1;

	m_active = false;

	m_textureSheet = AssignTexture(properties->particleTextureID);
}

Particle::~Particle()
{

}

void Particle::OnStart(Vector2 localSpawnPosition, const float currentTime)
{
	m_p_localPosition = localSpawnPosition;
	m_lifetime = properties->GetLifetimeVariance();

	m_imageIndex = 0;

	m_v_speed = ParticleProperties::EvaluateOverLifetime(properties->speedOverLifetime, 0);
	m_v_speedMult = Random::Range(properties->speedVarianceMult.x, properties->speedVarianceMult.y);

	m_v_direction = properties->GetRandomizedDirection();

	m_rotation = ParticleProperties::EvaluateOverLifetime(properties->rotationSpeedOverLifetime, 0);
	m_rotationMult = Random::Range(properties->rotationVarianceMult.x, properties->rotationVarianceMult.y);

	m_sizeScale = ParticleProperties::EvaluateOverLifetime(properties->sizeOverLifetime, 0);
	m_sizeMult = Random::Range(properties->sizeVarianceMult.x, properties->sizeVarianceMult.y);

	m_imgSpeedMult = Random::Range(properties->imageCycleVarianceMult.x, properties->imageCycleVarianceMult.y);

	if (properties->particleTextureID == ParticleTextureID::EXPLOSION)
		std::cout << properties->sizeVarianceMult.x << " frigoliti" << std::endl;

	m_currentAge = 0;

	m_active = true;
}

bool Particle::OnParticleSystemUpdate(float fixedTimeStep, float currentTime)
{
	m_currentAge += fixedTimeStep;

	const float normalizedAge = m_currentAge / m_lifetime;



	const float dir_r = m_v_direction * deg2Rad;



	m_imageIndex += ParticleProperties::EvaluateOverLifetime(properties->imageCycleSpeedOverLifetime, normalizedAge) * m_imgSpeedMult;

	m_v_speed = ParticleProperties::EvaluateOverLifetime(properties->speedOverLifetime, normalizedAge) * m_v_speedMult;

	m_rotation += ParticleProperties::EvaluateOverLifetime(properties->rotationSpeedOverLifetime, normalizedAge) * m_rotationMult;

	m_sizeScale = ParticleProperties::EvaluateOverLifetime(properties->sizeOverLifetime, normalizedAge) * m_sizeMult;

	Vector2 translation = Vector2(sin(dir_r), -cos(dir_r)) * m_v_speed;

	m_p_localPosition += translation;

	m_active = normalizedAge < 1.0f;

	return m_active;
}

void Particle::OnRender()
{


	Vector2 renderPos = *origin + m_p_localPosition;

	SDL_FRect sizeAndPiv = properties->sizeAndPivot;
	SDL_Rect renderRect =
	{
		renderPos.x - sizeAndPiv.w * sizeAndPiv.x * m_sizeScale,
		renderPos.y - sizeAndPiv.h * sizeAndPiv.y * m_sizeScale,
		sizeAndPiv.w * m_sizeScale,
		sizeAndPiv.h * m_sizeScale
	};

	ParticleTexture pp = particleTextures.at(properties->particleTextureID);

	const int renderImgIndex = (int)floor(m_imageIndex);//% pp.frameCount;
	SDL_Rect cellRect = { pp.cellSize.x * renderImgIndex, 0, pp.cellSize.x, pp.cellSize.y };

	if (renderImgIndex >= 0 && renderImgIndex < pp.frameCount)
	{

		std::cout << "img " << m_imageIndex << std::endl;

		SDL_RenderCopyEx(GameHandler::GetRenderer(), m_textureSheet, &cellRect, &renderRect, m_rotation, NULL, SDL_FLIP_NONE);
	}

}

void Particle::OnStop()
{
	m_active = false;
}

SDL_Texture* Particle::AssignTexture(const ParticleTextureID ptexID)
{
	if (m_texCache[ptexID] == nullptr)
	{
		ParticleTexture pt = particleTextures.at(ptexID);

		SDL_Surface* surf = IMG_Load(pt.path);
		if (surf == NULL)
			std::cout << "Image sheet loading error, is the path correct?" << std::endl;

		SDL_Texture* texture = SDL_CreateTextureFromSurface(GameHandler::GetRenderer(), surf);

		if (texture == NULL)
			std::cout << "Couldn't convert surface (created from IMG_Load) to SDL_Texture, error is: " << SDL_GetError() << std::endl;

		m_texCache[properties->particleTextureID] = texture;
		SDL_FreeSurface(surf);
	}

	SDL_Texture* result = m_texCache[properties->particleTextureID];

	return result;
}