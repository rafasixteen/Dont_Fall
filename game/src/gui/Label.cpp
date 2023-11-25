#include "Label.hpp"

#include <raygui.h>

namespace RGUI
{
	Label::Label(Vector2 position, const int size, const int spacing, Color color, std::string fontFilepath)
	{
		this->position = position;
		this->size = size;
		this->spacing = spacing;
		this->color = color;
		font = LoadFontEx(fontFilepath.c_str(), size , nullptr, 0);
	}

	Label::~Label()
	{
		UnloadFont(font);
	}

	void Label::Render(std::string text)
	{
		Vector2 textSize = MeasureTextEx(font, text.c_str(), size, spacing);
		textSize.x /= 2;
		textSize.y /= 2;

		DrawTextEx(font, text.c_str(), { position.x - textSize.x,position.y - textSize.y }, size, spacing, color);
	}
}