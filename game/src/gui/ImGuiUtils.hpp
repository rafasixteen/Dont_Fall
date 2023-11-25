#pragma once

#include <imgui.h>
#include "Stats.hpp"
#include "core/GameSettings.hpp"

namespace ImGui
{
	void ShowStatisticsMenu(PlayerStats playerStats);

	void ShowSettingsMenu(GameSettings& gameSettings);
}