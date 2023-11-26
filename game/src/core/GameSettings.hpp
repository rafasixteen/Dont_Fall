#pragma once

#include "AudioManager.hpp"

struct GameSettings
{
	struct AudioSettings
	{
		int masterVolume;
		int sfxVolume;
		int musicVolume;
	};

	struct GameplaySettings
	{
		bool showTimerWhilePlaying;
		bool showFPS;
		bool showHitboxes;
	};

	AudioSettings audioSettings;
	GameplaySettings gameplaySettings;

	GameSettings();

	static void DefaultGameSettings(GameSettings& gameSettings);
	static void DefaultAudioSettings(AudioSettings& audioSettings);
	static void DefaultGameplaySettings(GameplaySettings& gameplaySettings);

	std::string Serialize() const
	{
		std::ostringstream ss;
		ss
			<< audioSettings.masterVolume << " "
			<< audioSettings.sfxVolume << " "
			<< audioSettings.musicVolume << " "

			<< gameplaySettings.showTimerWhilePlaying << " "
			<< gameplaySettings.showFPS << " "
			<< gameplaySettings.showHitboxes << "\n";

		return ss.str();
	}

	void Deserialize(const std::string data)
	{
		std::istringstream ss(data);
		ss
			>> audioSettings.masterVolume
			>> audioSettings.sfxVolume
			>> audioSettings.musicVolume

			>> gameplaySettings.showTimerWhilePlaying
			>> gameplaySettings.showFPS
			>> gameplaySettings.showHitboxes;
	}

	bool operator!=(const GameSettings& other) const
	{
		return
			(this->gameplaySettings.showTimerWhilePlaying != other.gameplaySettings.showTimerWhilePlaying) ||
			(this->gameplaySettings.showFPS != other.gameplaySettings.showFPS) ||
			(this->gameplaySettings.showHitboxes != other.gameplaySettings.showHitboxes) ||

			(this->audioSettings.masterVolume != other.audioSettings.masterVolume) ||
			(this->audioSettings.sfxVolume != other.audioSettings.sfxVolume) ||
			(this->audioSettings.musicVolume != other.audioSettings.musicVolume);
	}
};
