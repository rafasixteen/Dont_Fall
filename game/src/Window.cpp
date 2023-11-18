#include "Window.hpp"
#include "raylib.h"

namespace Dont_Fall
{
	Window::Window(const int width, const int height)
	{
		InitWindow(width, height, windowName);
	}

	Window::~Window()
	{
		CloseWindow();
	}

}

