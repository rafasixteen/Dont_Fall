#include "GameSettings.hpp"
#include "Defines.hpp"

GameSettings::GameSettings()
{
	DefaultGameSettings(*this);
}

void GameSettings::DefaultGameSettings(GameSettings& gameSettings)
{
	DefaultAudioSettings(gameSettings.audioSettings);
	DefaultGameplaySettings(gameSettings.gameplaySettings);
}

void GameSettings::DefaultAudioSettings(AudioSettings& audioSettings)
{
	audioSettings.masterVolume = 30;
	audioSettings.sfxVolume = 20;
	audioSettings.musicVolume = 20;
}

void GameSettings::DefaultGameplaySettings(GameplaySettings& gameplaySettings)
{
	gameplaySettings.showTimerWhilePlaying = true;
	gameplaySettings.showFPS = true;
	gameplaySettings.showHitboxes = false;
	gameplaySettings.showCursor = true;
}

