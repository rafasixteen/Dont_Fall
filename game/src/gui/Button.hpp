#pragma once

#include <raylib.h>
#include "../core/Defines.hpp"
#include "../core/Utils.hpp"

namespace Dont_Fall::RGUI
{
	class Button
	{
	public:
		Button(Rectangle bounds, std::string name, Utils::Origin originAnchor = Utils::Origin::Center);
		~Button();

		void Render();
		bool IsClicked() const { return isClicked; }

	private:
		Vector2 origin{};
		Rectangle bounds;
		std::string name;
		bool isClicked = false;
	};
}