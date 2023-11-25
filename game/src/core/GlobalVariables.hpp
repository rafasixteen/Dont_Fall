#pragma once

#include <raylib.h>

namespace Core
{
	class GlobalVariables
	{
	public:
		static Vector2 screenCenter;
		static int currentWidth;
		static int currentHeight;
		static Vector2 ratio;

		static int initialWidth;
		static int initialHeight;

		static int minimunWindowWidth;
		static int minimunWindowHeight;

		static void UpdateGlobals();
	};
}
