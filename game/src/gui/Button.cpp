#include "Button.hpp"

namespace RGUI
{
	Button::Button(std::string name, ImVec2 size) : size{ size }, name{ name }
	{
	}

	Button::~Button()
	{
	}

	void Button::Render()
	{
		if (ImGui::Button(name.c_str(), size))
		{
			isClicked = true;
		}
		else
		{
			isClicked = false;
		}
	}
}