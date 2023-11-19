#include "GUI.hpp"
#include "../Game.hpp"
#include "../Gun.hpp"
#include <rlImGui.h>
#include "Stats.hpp"

namespace Dont_Fall::RGUI
{
	GUI::GUI(ImVec2 screenCenter) : screenCenter{ screenCenter }
	{
		// Initialization Done In Window.cpp
	}

	GUI::~GUI()
	{
		rlImGuiShutdown();
	}

	//---------------------------------------------------------------------------------------------//

	void GUI::UpdateStart()
	{
		if (playButton.IsClicked())
		{
			Game::Restart();
			Game::SetGameState(GameState::Gameplay);
		}

		if (statisticsButton.IsClicked())
		{
			Game::SetGameState(GameState::Statistics);
		}

		if (settingsButton.IsClicked())
		{
			Game::SetGameState(GameState::Settings);
		}

		if (exitButton.IsClicked())
		{
			exit(0);
		}
	}

	void GUI::RenderStart()
	{
		rlImGuiBegin();

		startMenu.Render();

		ImGui::End();

		rlImGuiEnd();
	}

	//---------------------------------------------------------------------------------------------//

	void GUI::UpdateGameOver()
	{
		if (homeButton.IsClicked())
		{
			Game::SetGameState(GameState::Start);
		}

		if (restartButton.IsClicked())
		{
			Game::Restart();
			Game::SetGameState(GameState::Gameplay);
		}
	}

	void GUI::RenderGameOver()
	{
		rlImGuiBegin();

		gameOverMenu.Render();

		ImGui::End();

		rlImGuiEnd();

		auto time = Stats::GetInstance().GetTime();
		std::string timeText = std::to_string(time);
		DrawText(timeText.c_str(), 100, 100, 40, BLACK);
	}

	//---------------------------------------------------------------------------------------------//

	void GUI::UpdatePaused()
	{
		if (homeButton.IsClicked())
		{
			Game::SetGameState(GameState::Start);
		}

		if (resumeButton.IsClicked())
		{
			Stats::GetInstance().ResumeTimer();
			Game::SetGameState(GameState::Gameplay);
		}
		
		if (settingsButton.IsClicked())
		{
			Game::SetGameState(GameState::Settings);
		}

		if (exitButton.IsClicked())
		{
			exit(0);
		}
	}

	void GUI::RenderPaused()
	{
		rlImGuiBegin();

		pausedMenu.Render();

		ImGui::End();

		rlImGuiEnd();

		DrawCurrentTime();
	}

	//---------------------------------------------------------------------------------------------//

	void GUI::UpdateGameplay()
	{

	}

	void GUI::RenderGameplay()
	{
		DrawAmmoCount();

		DrawCurrentTime();
	}

	//---------------------------------------------------------------------------------------------//

	void GUI::UpdateSettings()
	{

	}

	void GUI::RenderSettings()
	{
		DrawText("Settings", screenCenter.x, screenCenter.y, 100, BLACK);
	}

	//---------------------------------------------------------------------------------------------//

	void GUI::UpdateStatistics()
	{

	}

	void GUI::RenderStatistics()
	{
		DrawText("Statistics", screenCenter.x, screenCenter.y, 100, BLACK);
	}

	//---------------------------------------------------------------------------------------------//

	void GUI::DrawAmmoCount()
	{
		auto& map = GameObjectMap::GetInstance();
		int& ammoCount = map.FindByName("Gun").As<Gun>()->ammoCount;
		ammoLabel.Render(std::to_string(ammoCount).c_str());
	}

	void GUI::DrawCurrentTime()
	{
		auto time = Stats::GetInstance().GetElapsedTime();
		std::string timeText = std::to_string(time);
		DrawText(timeText.c_str(), 100, 100, 40, BLACK);
	}

	void GUI::SetCustomStyle()
	{
		ImGuiStyle& style = ImGui::GetStyle();

		style.WindowPadding = ImVec2(10, 10);
		style.WindowRounding = 4.0f;
		style.FramePadding = ImVec2(6, 6);
		style.FrameRounding = 5.0f;
		style.ItemSpacing = ImVec2(8, 8);
		style.ItemInnerSpacing = ImVec2(4, 4);
		style.IndentSpacing = 20.0f;
		style.ScrollbarSize = 16.0f;
		style.ScrollbarRounding = 8.0f;
		style.GrabMinSize = 8.0f;
		style.GrabRounding = 2.0f;
	}
}