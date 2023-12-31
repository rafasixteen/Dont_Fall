#include "Window.hpp"
#include "raylib.h"
#include "core/GlobalVariables.hpp"

Window::Window(const int width, const int height)
{
	InitWindow(width, height, windowName);

	Image icon = LoadImage("Assets/Sprites/Logo.png");
	SetWindowIcon(icon);
	UnloadImage(icon);

	SetWindowMinSize(Core::GlobalVariables::minimunWindowWidth, Core::GlobalVariables::minimunWindowHeight);
	Core::GlobalVariables::UpdateGlobals();
}

Window::~Window()
{
	CloseWindow();
}



