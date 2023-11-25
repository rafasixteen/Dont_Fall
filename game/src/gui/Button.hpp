#pragma once

#include <raylib.h>
#include <imgui.h>
#include "../core/Defines.hpp"
#include "../core/Utils.hpp"
#include "GUIElement.hpp"

namespace RGUI
{
	class Button : public GUIElement
	{
	public:
		Button(std::string name, ImVec2 size);
		~Button();

		void Render() override;
		bool IsClicked() const { return isClicked; }
		ImVec2 GetSize() const override { return size; }

	private:
		ImVec2 size;
		std::string name;
		bool isClicked = false;
	};
}