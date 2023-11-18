#include "Button.hpp"

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

namespace Dont_Fall::RGUI
{
	Button::Button(Rectangle bounds, std::string name, Utils::Origin originAnchor) : bounds{ bounds }, name{ name }
	{
		origin = Utils::GetOrigin(bounds.width, bounds.height, originAnchor);
	}

	Button::~Button()
	{
	}

	void Button::Render()
	{
		if (GuiButton({ bounds.x - origin.x,bounds.y - origin.y,bounds.width,bounds.height }, name.c_str()))
		{
			isClicked = true;
		}
		else
		{
			isClicked = false;
		}
	}
}