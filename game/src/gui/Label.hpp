#pragma once

#include <raylib.h>
#include "../core/Defines.hpp"
#include "../core/Utils.hpp"

namespace Dont_Fall::RGUI
{
	class Label
	{
	public:
		Label(Vector2 position, const int size, const int spacing, Color color, std::string fontFilepath);
		~Label();

		void Render(std::string text);

	private:
		Vector2 position{};
		int size;
		int spacing;
		Color color;
		Font font;
	};
}