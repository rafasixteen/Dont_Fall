#pragma once

#include "Button.hpp"
#include "Menu.hpp"
#include "Label.hpp"

namespace Dont_Fall::RGUI
{
	class GUI
	{
	public:
		GUI(ImVec2 screenCenter);
		~GUI();

		void UpdateStart();
		void RenderStart();

		void UpdateGameOver();
		void RenderGameOver();

		void UpdatePaused();
		void RenderPaused();

		void UpdateGameplay();
		void RenderGameplay();

		void UpdateSettings();
		void RenderSettings();

		void UpdateStatistics();
		void RenderStatistics();

		static void SetCustomStyle();
	private:
		void DrawAmmoCount();
		void DrawCurrentTime();

		ImVec2 screenCenter{};

		ImVec2 buttonSize{ 200,50 };
		ImVec2 menuPosition{ 200,50 };

		Button homeButton{ "Home", buttonSize };
		Button playButton{ "Play",buttonSize };
		Button restartButton{ "Restart",buttonSize };
		Button resumeButton{ "Resume",buttonSize };

		Button statisticsButton{ "Statistics",buttonSize };
		Button settingsButton{ "Settings",buttonSize };
		Button exitButton{ "Exit",buttonSize };

		// StartMenu //
		std::vector<GUIElement*> startMenuButtons = { &playButton, &statisticsButton, &settingsButton, &exitButton };
		Menu startMenu{ "StartMenu",screenCenter ,&startMenuButtons };
		// StartMenu //

		// GameOverMenu //
		std::vector<GUIElement*> gameOverMenuButtons = { &restartButton ,&homeButton };
		Menu gameOverMenu{ "GameOverMenu",screenCenter ,&gameOverMenuButtons };
		// GameOverMenu //

		// GameplayMenu //
		std::vector<GUIElement*> gameplayMenuButtons = { &playButton, &statisticsButton, &settingsButton, &exitButton };
		Menu gameplayMenu{ "GameplayMenu",screenCenter ,&gameplayMenuButtons };
		// GameplayMenu //

		// PausedMenu //
		std::vector<GUIElement*> pausedMenuButtons = { &resumeButton ,&homeButton , &settingsButton, &exitButton };
		Menu pausedMenu{ "PausedMenu",screenCenter ,&pausedMenuButtons };
		// PausedMenu //

		// SettingsMenu //
		std::vector<GUIElement*> settingsMenuButtons = {  };
		Menu SettingsMenu{ "SettingsMenu",screenCenter ,&settingsMenuButtons };
		// PausedMenu //

		// StatisticsMenu //
		std::vector<GUIElement*> statisticsMenuButtons = { };
		Menu statisticsMenu{ "StatisticsMenu",screenCenter ,&statisticsMenuButtons };
		// StatisticsMenu //

		Label ammoLabel{ {screenCenter.x,screenCenter.y} ,100,0,BLACK,"Assets/Fonts/Roboto/Roboto-Medium.ttf" };
	};
}
