#include "pch.h"
#include "AudioManager.h"

namespace FieaGameEngine
{

	AudioManager* AudioManager::mInstance = nullptr;




	AudioManager* AudioManager::Instance()
	{
		if (mInstance == nullptr)
		{
			mInstance = new AudioManager();
			mInstance->mSoundSystem = std::make_unique<SoundSystem>();
		}

		return mInstance;
	}




	void AudioManager::Init()
	{
		for (auto& sound : mSounds)
		{
			mSoundSystem->CreateSound(&(sound.second.second), sound.second.first.c_str());
		}
	}




	void AudioManager::Update(WorldState& worldState)
	{
		UNREFERENCED_PARAMETER(worldState);
		//do nothing
	}




	void AudioManager::Shutdown()
	{
		for (auto& sound : mSounds)
		{
			mSoundSystem->ReleaseSound(sound.second.second);
		}

		delete AudioManager::Instance();
	}




	void AudioManager::Play(const std::string& soundName, bool looping)
	{
		mSoundSystem->Play(mSounds.At(soundName).second, looping);
	}




	void AudioManager::AddSound(const std::string& soundName, const std::string& soundDirectory)
	{
		Sound sound;
		mSounds.Insert(std::make_pair(soundName, std::make_pair(soundDirectory, sound)));
	}




	Sound& AudioManager::GetSound(const std::string& soundName)
	{
		return mSounds.At(soundName).second;
	}

}