#include "Window.hpp"
#include "raylib.h"
#include <rlImGui.h>
#include "core/GlobalVariables.hpp"
#include "gui/GUI.hpp"

Window::Window(const int width, const int height)
{
	InitWindow(width, height, windowName);

	Image icon = LoadImage("Assets/Sprites/Logo.png");
	SetWindowIcon(icon);
	UnloadImage(icon);

	SetWindowMinSize(Core::GlobalVariables::minimunWindowWidth, Core::GlobalVariables::minimunWindowHeight);

	rlImGuiSetup(true);
	RGUI::GUI::SetCustomStyle();
	RGUI::GUI::SetCustomColors();

	Core::GlobalVariables::UpdateGlobals();
}

Window::~Window()
{
	CloseWindow();
}



