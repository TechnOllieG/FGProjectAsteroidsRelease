#include "AudioManager.h"
#include <iostream>

std::map<AudioID, Mix_Chunk*> AudioManager::m_audioMap = std::map<AudioID, Mix_Chunk*>();
std::map<AudioID, int> AudioManager::m_loopedChannelMap = std::map<AudioID, int>();

AudioManager::AudioManager()
{
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 256) == -1)
	{
		std::cout << "Failed to initialize audio: " << SDL_GetError() << std::endl;
		exit(-1);
	}

	// Loads all sound files specified in Assets.h to memory in Mix_Chunk*'s and initializes the m_loopedChannelMap with all -1 since no sounds are looped at start
	for (Sound sound : sounds)
	{
		Mix_Chunk* chunk = Mix_LoadWAV(sound.path);
		if(chunk == nullptr)
		{
			std::cout << "Failed to load wave file with path: " << sound.path << ", error is: " << SDL_GetError() << std::endl;
			exit(-1);
		}
		m_audioMap[sound.audioID] = chunk;
		m_loopedChannelMap[sound.audioID] = -1;
	}
}

AudioManager::~AudioManager()
{
	// Stops all sounds before freeing sound resources
	Mix_HaltChannel(-1);

	for (const std::pair<AudioID, Mix_Chunk*> pair : m_audioMap)
	{
		Mix_FreeChunk(pair.second);
	}
	m_audioMap.clear();
}

void AudioManager::PlaySound(AudioID id)
{
	if (Mix_PlayChannel(-1, m_audioMap[id], 0) == -1)
	{
		std::cout << "Failed to play sound: " << SDL_GetError() << std::endl;
		exit(-1);
	}
}

void AudioManager::PlaySoundLooped(AudioID id)
{
	int channel;
	if ((channel = Mix_PlayChannel(-1, m_audioMap[id], -1)) == -1)
	{
		std::cout << "Failed to play sound: " << SDL_GetError() << std::endl;
		exit(-1);
	}
	m_loopedChannelMap[id] = channel;
}

void AudioManager::StopLoopedSound(AudioID id, int fadeOutTimeMs)
{
	int channel = m_loopedChannelMap[id];

	if (channel == -1)
	{
		std::cout << "AudioManager: Don't need to stop looping since the specified sound is not currently looped" << std::endl;
		return;
	}

	if (fadeOutTimeMs == -1)
		Mix_HaltChannel(channel);
	else
		Mix_FadeOutChannel(channel, fadeOutTimeMs);
}