#pragma once

struct GameSettings
{
	bool showTimerWhilePlaying;
	int ammoCount;
	int obstaclesCount;

	GameSettings()
	{
		DefaultGameSettings(*this);
	}

	static void DefaultGameSettings(GameSettings& gameSettings)
	{
		gameSettings.showTimerWhilePlaying = false;

		gameSettings.ammoCount = 3;
		gameSettings.obstaclesCount = 3;
	}
};
