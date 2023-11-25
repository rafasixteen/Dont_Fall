#pragma once

#include <imgui.h>
#include "Stats.hpp"
#include "core/GameSettings.hpp"

namespace ImGui
{
	void ShowStatisticsMenu(Dont_Fall::PlayerStats playerStats);

	void ShowSettingsMenu(Dont_Fall::GameSettings& gameSettings);
}