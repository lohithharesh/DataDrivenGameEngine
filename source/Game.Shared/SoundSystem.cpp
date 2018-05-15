#include "pch.h"
#include "SoundSystem.h"

namespace FieaGameEngine
{

	SoundSystem::SoundSystem()
	{
		if (FMOD::System_Create(&mSystem) != FMOD_OK)
		{
			return;
		}
		
		std::int32_t driverCount = 0;
		mSystem->getNumDrivers(&driverCount);
		if (driverCount == 0)
		{
			return;
		}

		mSystem->init(12, FMOD_INIT_NORMAL, nullptr);
	}




	void SoundSystem::CreateSound(Sound* pSound, const char* pFile)
	{
		mSystem->createSound(pFile, FMOD_DEFAULT, 0, pSound);
	}




	void SoundSystem::Play(Sound& pSound, bool loop)
	{
		if (!loop)
		{
			pSound->setMode(FMOD_LOOP_OFF);
		}
		else
		{
			pSound->setMode(FMOD_LOOP_NORMAL);
			pSound->setLoopCount(-1);
		}

		mSystem->playSound(pSound, 0, false, 0);
	}




	void SoundSystem::ReleaseSound(Sound& pSound)
	{
		pSound->release();
	}




	void SoundSystem::Shutdown()
	{
		delete mSystem;
	}

}