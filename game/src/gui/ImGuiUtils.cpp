#include "ImGuiUtils.hpp"
#include "core/GlobalVariables.hpp"

namespace ImGui
{
	void ShowStatisticsMenu(Dont_Fall::PlayerStats playerStats)
	{
		ImGui::Begin("Player Statistics", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

		std::string formmatedTime = "Time: ";
		formmatedTime += Dont_Fall::Stats::FormatTime(playerStats.time);

		ImGui::Text(formmatedTime.c_str());
		ImGui::Text("Games Played: %d", playerStats.gamesPlayed);
		ImGui::Text("Times Died: %d", playerStats.died);
		ImGui::Text("Ammo Collected: %d", playerStats.ammoCollected);

		ImGui::End();
	}

	void ShowSettingsMenu(Dont_Fall::GameSettings& gameSettings)
	{
		ImGui::Begin("Game Settings", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

		ImGui::SetWindowSize("Game Settings", { 400,400 });
		ImGui::SetWindowPos("Game Settings", { (1280 / 2) - 200,(720 / 2) - 200 });

		//ImGui::Checkbox("Show Timer While Playing", &gameSettings.showTimerWhilePlaying);
		//ImGui::SliderInt("Ammo Slider", &gameSettings.ammoCount, 1, 10);
		//ImGui::SliderInt("Obstacles Slider", &gameSettings.obstaclesCount, 1, 10);

		ImGui::End();
	}
}

