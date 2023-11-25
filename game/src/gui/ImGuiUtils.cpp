#include "ImGuiUtils.hpp"
#include "core/GlobalVariables.hpp"

namespace ImGui
{
	void ShowStatisticsMenu(PlayerStats playerStats)
	{
		ImGui::Begin("Player Statistics", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

		ImVec2 size = { 400 * Core::GlobalVariables::ratio.x,400 * Core::GlobalVariables::ratio.y };
		ImGui::SetWindowSize("Player Statistics", size);
		ImGui::SetWindowPos("Player Statistics", { Core::GlobalVariables::screenCenter.x - size.x/2,Core::GlobalVariables::screenCenter.y - size.y/2 });

		std::string formmatedTime = "Time: ";
		formmatedTime += Stats::FormatTime(playerStats.time);

		ImGui::Text(formmatedTime.c_str());
		ImGui::Text("Games Played: %d", playerStats.gamesPlayed);
		ImGui::Text("Times Died: %d", playerStats.died);
		ImGui::Text("Ammo Collected: %d", playerStats.ammoCollected);

		ImGui::End();
	}

	void ShowSettingsMenu(GameSettings& gameSettings)
	{
		ImGui::Begin("Game Settings", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

		ImVec2 size = { 400 * Core::GlobalVariables::ratio.x,400 * Core::GlobalVariables::ratio.y };
		ImGui::SetWindowSize("Game Settings", size);
		ImGui::SetWindowPos("Game Settings", { Core::GlobalVariables::screenCenter.x - size.x / 2,Core::GlobalVariables::screenCenter.y - size.y / 2 });

		ImGui::Checkbox("Show Timer While Playing", &gameSettings.showTimerWhilePlaying);
		ImGui::SliderInt("Ammo Slider", &gameSettings.ammoCount, 1, 10);
		ImGui::SliderInt("Obstacles Slider", &gameSettings.obstaclesCount, 1, 10);


		ImGui::End();
	}
}

