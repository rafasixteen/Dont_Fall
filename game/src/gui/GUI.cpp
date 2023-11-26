#include "GUI.hpp"
#include "../Game.hpp"
#include "../Gun.hpp"
#include <rlImGui.h>
#include "Stats.hpp"
#include <Player.hpp>
#include "ImGuiUtils.hpp"
#include "core/GlobalVariables.hpp"
#include "core/Utils.hpp"

namespace RGUI
{
	GUI::GUI()
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
			Game::StartGame();
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

		auto style = &ImGui::GetStyle();
		auto colors = style->Colors;

		ImVec4 purple = Utils::HexToRGBA("9757EFFF");
		ImVec4 purpleHover = Utils::HexToRGBA("8338ECFF");
		ImVec4 purpleActive = Utils::HexToRGBA("741FEAFF");

		colors[ImGuiCol_Button] = purple;
		colors[ImGuiCol_ButtonHovered] = purpleHover;
		colors[ImGuiCol_ButtonActive] = purpleActive;

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
			Game::StartGame();
		}
	}

	void GUI::RenderGameOver()
	{
		rlImGuiBegin();

		gameOverMenu.Render();

		ImGui::End();

		rlImGuiEnd();

		auto time = Stats::GetInstance().GetTime();
		DrawCurrentTimer(time);
	}

	//---------------------------------------------------------------------------------------------//

	void GUI::UpdatePaused()
	{
		if (homeButton.IsClicked())
		{
			Game::ResetGame();
			Game::SetGameState(GameState::Start);
		}

		if (resumeButton.IsClicked())
		{
			Stats::GetInstance().ResumeTimer();
			Game::SetGameState(GameState::Gameplay);
		}

		if (settingsButton.IsClicked())
		{
			Game::ResetGame();
			Game::SetGameState(GameState::Settings);
		}

		if (exitButton.IsClicked())
		{
			exit(0);
		}

		if (IsKeyPressed(KEY_ESCAPE)) { Game::SetGameState(GameState::Gameplay); stats.ResumeTimer(); }
	}

	void GUI::RenderPaused()
	{
		rlImGuiBegin();

		pausedMenu.Render();

		ImGui::End();

		rlImGuiEnd();

		if (Game::GetGameSettings().gameplaySettings.showTimerWhilePlaying == true)
		{
			auto time = stats.GetElapsedTime();
			DrawCurrentTimer(time);
		}
	}

	//---------------------------------------------------------------------------------------------//

	void GUI::UpdateGameplay()
	{
		if (IsKeyPressed(KEY_ESCAPE)) { Game::SetGameState(GameState::Paused); stats.PauseTimer(); }
	}

	void GUI::RenderGameplay()
	{
		auto& gameSettings = Game::GetGameSettings();

		DrawAmmoCount();

		if (gameSettings.gameplaySettings.showTimerWhilePlaying)
		{
			auto time = stats.GetElapsedTime();
			DrawCurrentTimer(time);
		}

		if (gameSettings.gameplaySettings.showFPS)
		{
			DrawFPS();
		}
	}

	//---------------------------------------------------------------------------------------------//

	void GUI::UpdateSettings()
	{
		if (IsKeyPressed(KEY_ESCAPE)) Game::SetGameState(GameState::Start);
	}

	void GUI::RenderSettings()
	{
		rlImGuiBegin();
		//ImGui::ShowSettingsMenu(Game::GetGameSettings());
		ImGui::ShowDemoWindow();
		rlImGuiEnd();
	}

	//---------------------------------------------------------------------------------------------//

	void GUI::UpdateStatistics()
	{
		if (IsKeyPressed(KEY_ESCAPE)) Game::SetGameState(GameState::Start);
	}

	void GUI::RenderStatistics()
	{
		auto playerStats = Stats::GetInstance().LoadStatsFromFile("stats.txt");

		rlImGuiBegin();
		ImGui::ShowStatisticsMenu(playerStats);
		rlImGuiEnd();
	}

	//---------------------------------------------------------------------------------------------//

	void GUI::DrawAmmoCount()
	{
		auto& map = GameObjectMap::GetInstance();
		int& ammoCount = map.FindByName("Gun").As<Gun>()->ammoCount;
		ammoLabel.Render(std::to_string(ammoCount).c_str());
	}

	void GUI::DrawFPS()
	{
		int fps = GetFPS();

		Color color = LIME;
		if ((fps < 30) && (fps >= 15)) color = ORANGE;
		else if (fps < 15) color = RED;

		DrawText(TextFormat("%2i FPS", fps), 0, 0, 20, color);
	}

	void GUI::DrawCurrentTimer(int milliseconds)
	{
		std::string timeText = Stats::FormatTime(milliseconds);
		timeLabel.Render(timeText.c_str());
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

	void GUI::SetCustomColors()
	{
		ImGuiStyle* style = &ImGui::GetStyle();
		ImVec4* colors = style->Colors;

		colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);

		colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);

		colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

		colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.29f, 0.48f, 0.54f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);

		colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.29f, 0.48f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);

		colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);

		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);

		colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);

		colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);

		colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);

		colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);

		colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);

		colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);

		colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);

		colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
		colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
		colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
		colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);

		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);

		colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);

		colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);

		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
	}
}