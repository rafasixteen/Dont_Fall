#include "Utils.hpp"
#include <raylib.h>

namespace Utils
{
	void DrawFrameTime(int posX, int posY, float frameTime)
	{
		std::string text = "Frame Time: " + std::to_string(frameTime);
		DrawText(text.c_str(), posX, posY, 24, BLACK);
	}

	void DrawFPS(int posX, int posY, int fps)
	{
		std::string text = "FPS: " + std::to_string(fps);
		DrawText(text.c_str(), posX, posY, 24, BLACK);
	}

	Vector2 GetOrigin(float width, float height, Origin originAnchor)
	{
		Vector2 origin{};

		switch (originAnchor)
		{
		case Origin::TopLeft:
			origin = { 0,0 };
			break;
		case Origin::TopRight:
			origin = { width,0 };
			break;
		case Origin::BottomLeft:
			origin = { 0,height };
			break;
		case Origin::BottomRight:
			origin = { width,height };
			break;
		case Origin::Center:
			origin = { width * 0.5f,height * 0.5f };
			break;
		case Origin::LeftCenter:
			origin = { 0,height * 0.5f };
			break;
		case Origin::RightCenter:
			origin = { width,height * 0.5f };
			break;
		case Origin::TopCenter:
			origin = { width * 0.5f,0 };
			break;
		case Origin::BottomCenter:
			origin = { width * 0.5f,height };
			break;
		default:
			WARNING("Invalid Origin Anchor");
			break;
		}

		return origin;
	}
}