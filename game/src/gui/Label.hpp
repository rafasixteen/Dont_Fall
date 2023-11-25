#pragma once

#include <raylib.h>
#include "../core/Defines.hpp"
#include "../core/Utils.hpp"

namespace RGUI
{
	class Label
	{
	public:
		Label(Vector2 position, const int size, const int spacing, Color color, std::string fontFilepath);
		~Label();

		void Render(std::string text);
		void SetPosition(Vector2 newPosition) { position = newPosition; }
		void SetSize(int newSize) { size = newSize; }

	private:
		Vector2 position{};
		int size;
		int spacing;
		Color color;
		Font font;
	};
}