#pragma once

#include "SoundSystem.h"
#include "WorldState.h"
#include "HashMap.h"
#include <utility>
#include <memory>

namespace FieaGameEngine
{

	class AudioManager
	{

	public:

		~AudioManager() = default;

		static AudioManager* Instance();

		void Init();
		void Update(WorldState& worldState);
		void Shutdown();

		void Play(const std::string& soundName, bool looping);

		void AddSound(const std::string& soundName, const std::string& soundDirectory);
		Sound& GetSound(const std::string& soundName);

	private:

		AudioManager() = default;

		static AudioManager* mInstance;
		std::unique_ptr<SoundSystem> mSoundSystem;

		HashMap<std::string, std::pair<std::string, Sound>> mSounds;

	};

}