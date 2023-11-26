#pragma once

struct GameSettings
{
	struct AudioSettings
	{
		int masterVolume;
		int sfxVolume;
		int musicVolume;

		bool playMusic;
	};

	struct GameplaySettings
	{
		bool showTimerWhilePlaying;
		bool showFPS;
		bool showHitboxes;
	};

	AudioSettings audioSettings;
	GameplaySettings gameplaySettings;

	GameSettings()
	{
		DefaultGameSettings(*this);
	}

	static void DefaultGameSettings(GameSettings& gameSettings)
	{
		gameSettings.audioSettings.masterVolume = 5;
		gameSettings.audioSettings.sfxVolume = 100;
		gameSettings.audioSettings.musicVolume = 100;
		gameSettings.audioSettings.playMusic = true;

		gameSettings.gameplaySettings.showTimerWhilePlaying = true;
		gameSettings.gameplaySettings.showFPS = true;
		gameSettings.gameplaySettings.showHitboxes = false;
	}
};
