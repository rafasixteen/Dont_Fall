#include "Window.hpp"
#include "raylib.h"
#include <rlImGui.h>

#include "gui/GUI.hpp"

namespace Dont_Fall
{
	Window::Window(const int width, const int height)
	{
		InitWindow(width, height, windowName);

		//SetWindowIcon();
		SetWindowMinSize(WIDTH / 1.5f, HEIGHT / 1.5f);

		//SetWindowState(FLAG_WINDOW_RESIZABLE);

		rlImGuiSetup(true);
		Dont_Fall::RGUI::GUI::SetCustomStyle();
	}

	Window::~Window()
	{
		CloseWindow();
	}

}

