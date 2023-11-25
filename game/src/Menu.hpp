#pragma once

#include <raylib.h>
#include <imgui.h>
#include "core/Defines.hpp"
#include "core/Utils.hpp"
#include <gui/Button.hpp>

namespace RGUI
{
	class Menu
	{
	public:
		Menu(std::string name, ImVec2 position, std::vector<GUIElement*>* elements, Utils::Origin originAnchor = Utils::Origin::Center);
		~Menu() = default;

		void Render();

	private:
		std::string name;
		std::vector<GUIElement*>* elements;

		ImVec2 size{};
		ImVec2 position{};
	};
}