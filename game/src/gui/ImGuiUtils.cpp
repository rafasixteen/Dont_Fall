#include "ImGuiUtils.hpp"
#include "core/GlobalVariables.hpp"
#include "Game.hpp"

namespace ImGui
{
	void ShowStatisticsMenu(PlayerStats playerStats)
	{
		ImGui::Begin("Player Statistics", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

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

	void ShowAudioSettings(GameSettings& gameSettings)
	{
		Vector2 ratio = Core::GlobalVariables::ratio;

		ImGui::Begin("Audio Settings", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground);

		ImVec2 size = { 400 * ratio.x,200 * ratio.y };
		ImVec2 position = { 340 * ratio.x,0 };
		ImGui::SetWindowSize("Audio Settings", size);
		ImGui::SetWindowPos("Audio Settings", position);

		ImGui::SliderInt(" Master Volume", &gameSettings.audioSettings.masterVolume, 0, 100);
		ImGui::SliderInt(" SFX Volume", &gameSettings.audioSettings.sfxVolume, 0, 100);
		ImGui::SliderInt(" Music Volume", &gameSettings.audioSettings.musicVolume, 0, 100);

		ImGui::End();
	}

	void ShowGameplaySettings(GameSettings& gameSettings)
	{
		Vector2 ratio = Core::GlobalVariables::ratio;

		ImGui::Begin("Gameplay Settings", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground);

		ImVec2 size = { 400 * ratio.x,200 * ratio.y };
		ImVec2 position = { 340 * ratio.x,0 };
		ImGui::SetWindowSize("Gameplay Settings", size);
		ImGui::SetWindowPos("Gameplay Settings", position);

		ImGui::Checkbox(" Show Timer While Playing", &gameSettings.gameplaySettings.showTimerWhilePlaying);
		ImGui::Checkbox(" Show FPS", &gameSettings.gameplaySettings.showFPS);
		ImGui::Checkbox(" Show Hitboxes", &gameSettings.gameplaySettings.showHitboxes);

		ImGui::End();
	}

	enum ActiveSettingsSection
	{
		Gameplay,
		Audio,
	};

	void ShowSettingsMenu(GameSettings& gameSettings)
	{
		static auto previousGameSettings = gameSettings;
		static ActiveSettingsSection activeSettingsSection = ActiveSettingsSection::Audio;
		Vector2 ratio = Core::GlobalVariables::ratio;

		ImGui::Begin("Game Settings", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground);

		ImVec2 size = { static_cast<float>(Core::GlobalVariables::currentWidth / 2), static_cast<float>(Core::GlobalVariables::currentHeight) };
		ImVec2 position = { 0,0 };
		ImGui::SetWindowSize("Game Settings", size);
		ImGui::SetWindowPos("Game Settings", position);

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 40));

		ImVec2 buttonSize = { 200 * ratio.x,50 * ratio.y };
		if (activeSettingsSection == ActiveSettingsSection::Audio) { SetCursorPosX(50.0f * ratio.x); }
		if (ImGui::Button("AUDIO", buttonSize)) { activeSettingsSection = ActiveSettingsSection::Audio; }
		if (activeSettingsSection == ActiveSettingsSection::Gameplay) { SetCursorPosX(50.0f * ratio.x); }
		if (ImGui::Button("GAMEPLAY", buttonSize)) { activeSettingsSection = ActiveSettingsSection::Gameplay; }

		ImGui::PopStyleVar();

		if (activeSettingsSection == ActiveSettingsSection::Gameplay) { ShowGameplaySettings(previousGameSettings); }
		if (activeSettingsSection == ActiveSettingsSection::Audio) { ShowAudioSettings(previousGameSettings); }

		if (gameSettings != previousGameSettings)
		{
			ImGui::SetCursorPosY(Core::GlobalVariables::currentHeight - 60);
			if (ImGui::Button("CONFIRM CHANGES", buttonSize))
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