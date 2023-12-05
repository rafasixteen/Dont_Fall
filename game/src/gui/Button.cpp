#include "Button.hpp"
#include <core/GlobalVariables.hpp>

namespace RGUI
{
	void Button::Render()
	{
		if (ImGui::Button(name.c_str(), { size.x * Core::GlobalVariables::ratio.x,size.y * Core::GlobalVariables::ratio.y }))
		{
			isClicked = true;
		}
		else
		{
			isClicked = false;
		}
	}
}