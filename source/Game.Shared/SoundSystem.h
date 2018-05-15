#pragma once

#include "fmod/fmod.hpp"
#include "fmod/fmod_errors.h"

namespace FieaGameEngine
{

	typedef FMOD::Sound* Sound;

	class SoundSystem
	{
	public:
		SoundSystem();
		SoundSystem(const SoundSystem& other) = delete;
		SoundSystem(SoundSystem&& other) = default;
		SoundSystem& operator=(const SoundSystem& other) = delete;
		SoundSystem& operator=(SoundSystem&& other) = default;
		~SoundSystem() = default;

		void CreateSound(Sound* pSound, const char* pFile);
		void Play(Sound& pSound, bool loop);
		void ReleaseSound(Sound& pSound);

	private:

		FMOD::System* mSystem;
		void Shutdown();

	};

}