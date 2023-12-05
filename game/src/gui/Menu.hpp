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
		Menu(std::string name, std::vector<GUIElement*>* elements) : name{ name }, elements{ elements } {}
		~Menu() = default;

		void Render();

	private:
		std::string name;
		std::vector<GUIElement*>* elements;
	};
}