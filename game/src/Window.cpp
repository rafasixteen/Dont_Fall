#include "Window.hpp"
#include "raylib.h"
#include <rlImGui.h>
#include "core/GlobalVariables.hpp"
#include "gui/GUI.hpp"

Window::Window(const int width, const int height)
{
	InitWindow(width, height, windowName);

	//SetWindowIcon();
	SetWindowMinSize(Core::GlobalVariables::minimunWindowWidth, Core::GlobalVariables::minimunWindowHeight);

	SetWindowState(FLAG_WINDOW_RESIZABLE);

	rlImGuiSetup(true);
	RGUI::GUI::SetCustomStyle();

	Core::GlobalVariables::UpdateGlobals();
}

Window::~Window()
{
	CloseWindow();
}



