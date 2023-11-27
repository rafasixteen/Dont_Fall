#include "GlobalVariables.hpp"
#include "Defines.hpp"

namespace Core
{
	Vector2 GlobalVariables::screenCenter = { 0,0 };
	int GlobalVariables::currentWidth = 0;
	int GlobalVariables::currentHeight = 0;
	Vector2 GlobalVariables::ratio = { 0,0 };

	int GlobalVariables::initialWidth = 1280;
	int GlobalVariables::initialHeight = 720;

	int GlobalVariables::minimunWindowWidth = 850;
	int GlobalVariables::minimunWindowHeight = 480;

	void GlobalVariables::UpdateGlobals()
	{
		currentWidth = GetScreenWidth();
		currentHeight = GetScreenHeight();

		screenCenter = { static_cast<float>(currentWidth / 2),static_cast<float>(currentHeight / 2) };

		ratio.x = static_cast<float>(currentWidth) / initialWidth;
		ratio.y = static_cast<float>(currentHeight) / initialHeight;

		INFO(ratio.x);
		INFO(ratio.y);
	}
}