#pragma once

#include "Button.hpp"
#include "Menu.hpp"
#include "Label.hpp"
#include "../Stats.hpp"
#include "core/GlobalVariables.hpp"

namespace RGUI
{
	class GUI
	{
	public:
		GUI();
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
		static void SetCustomColors();
	private:
		void DrawAmmoCount();
		void DrawFPS();
		void DrawCurrentTimer(int milliseconds);

		Stats& stats = Stats::GetInstance();
		ImVec2 screenCenter = { Core::GlobalVariables::screenCenter.x, Core::GlobalVariables::screenCenter.y };

		ImVec2 buttonSize{ 200,50 };

		Button homeButton{ "Home", buttonSize };
		Button playButton{ "Play",buttonSize };
		Button restartButton{ "Restart",buttonSize };
		Button resumeButton{ "Resume",buttonSize };

		Button statisticsButton{ "Statistics",buttonSize };
		Button settingsButton{ "Settings",buttonSize };
		Button exitButton{ "Exit",buttonSize };

		std::vector<GUIElement*> startMenuButtons = { &playButton, &statisticsButton, &settingsButton, &exitButton };
		Menu startMenu{ "StartMenu" ,&startMenuButtons };

		std::vector<GUIElement*> gameOverMenuButtons = { &restartButton ,&homeButton };
		Menu gameOverMenu{ "GameOverMenu" ,&gameOverMenuButtons };

		std::vector<GUIElement*> gameplayMenuButtons = { &playButton, &statisticsButton, &settingsButton, &exitButton };
		Menu gameplayMenu{ "GameplayMenu" ,&gameplayMenuButtons };

		std::vector<GUIElement*> pausedMenuButtons = { &resumeButton ,&homeButton , &settingsButton, &exitButton };
		Menu pausedMenu{ "PausedMenu" ,&pausedMenuButtons };

		Label ammoLabel{ {screenCenter.x,screenCenter.y} ,100,0,BLACK,"Assets/Fonts/Roboto/Roboto-Medium.ttf" };
		Label timeLabel{ {screenCenter.x,(screenCenter.y /= 2) - 100} ,30,0,BLACK,"Assets/Fonts/Roboto/Roboto-Medium.ttf" };
		Label fpsLabel{ {0,0},20,0,BLACK,"Assets/Fonts/Roboto/Roboto-Medium.ttf" };
	};
}
