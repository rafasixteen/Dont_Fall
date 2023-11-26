#include "ImGuiUtils.hpp"
#include "core/GlobalVariables.hpp"
#include "Game.hpp"

namespace ImGui
{
	void ShowStatisticsMenu(PlayerStats playerStats)
	{
		ImGui::Begin("Player Statistics", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground);

		ImVec2 size = { 400 ,400 };
		ImGui::SetWindowSize("Player Statistics", size);
		ImGui::SetWindowPos("Player Statistics", { Core::GlobalVariables::screenCenter.x - size.x / 2,Core::GlobalVariables::screenCenter.y - size.y / 2 });

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
		static auto previousGameSettings = gameSettings;

		ImGui::Begin("Game Settings", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground);

		ImVec2 size = { static_cast<float>(Core::GlobalVariables::currentWidth), static_cast<float>(Core::GlobalVariables::currentHeight) };
		ImGui::SetWindowSize("Game Settings", size);
		ImGui::SetWindowPos("Game Settings", { Core::GlobalVariables::screenCenter.x - size.x / 2,Core::GlobalVariables::screenCenter.y - size.y / 2 });

		if (ImGui::CollapsingHeader("Gameplay Settings", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::Checkbox("Show Timer While Playing", &previousGameSettings.gameplaySettings.showTimerWhilePlaying);
			ImGui::Checkbox("Show FPS", &previousGameSettings.gameplaySettings.showFPS);
			ImGui::Checkbox("Show Hitboxes", &previousGameSettings.gameplaySettings.showHitboxes);
		}

		if (ImGui::CollapsingHeader("Audio Settings", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::SliderInt("Master Volume", &previousGameSettings.audioSettings.masterVolume, 0, 100);
			ImGui::SliderInt("SFX Volume", &previousGameSettings.audioSettings.sfxVolume, 0, 100);
			ImGui::SliderInt("Music Volume", &previousGameSettings.audioSettings.musicVolume, 0, 100);
		}

		if (gameSettings != previousGameSettings)
		{
			if (ImGui::Button("Confirm Changes"))
			{
				gameSettings = previousGameSettings;

				SetMasterVolume(gameSettings.audioSettings.masterVolume / 100.0f);
				AudioManager::GetInstance().SetVolumeSFX(gameSettings.audioSettings.sfxVolume);
				AudioManager::GetInstance().SetVolumeMusic(gameSettings.audioSettings.musicVolume);

				Game::SaveSettingsToFile();
			}
		}

		ImGui::End();
	}
}

