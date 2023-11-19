#include "Window.hpp"
#include "raylib.h"

namespace Dont_Fall
{
	Window::Window(const int width, const int height)
	{
		InitWindow(width, height, windowName);

		//SetWindowIcon();
		SetWindowMinSize(WIDTH / 1.5f, HEIGHT / 1.5f);

		SetWindowState(FLAG_WINDOW_RESIZABLE);
		SetWindowState(FLAG_MSAA_4X_HINT);
	}

	Window::~Window()
	{
		CloseWindow();
	}

}

