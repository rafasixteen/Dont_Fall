#pragma once

#include <raylib.h>
#include <imgui.h>
#include "../core/Defines.hpp"
#include "../core/Utils.hpp"
#include "GUIElement.hpp"
#include "core/GlobalVariables.hpp"

namespace RGUI
{
	class Button : public GUIElement
	{
	public:
		Button(std::string name, ImVec2 size) : name{ name }, size{ size } {}
		~Button() {}

		void Render() override;
		bool IsClicked() const { return isClicked; }
		ImVec2 GetSize() const override { return { size.x * Core::GlobalVariables::ratio.x,size.y * Core::GlobalVariables::ratio.y }; }

	private:
		ImVec2 size;
		std::string name;
		bool isClicked = false;
	};
}