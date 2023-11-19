#include "guiTest.hpp"

#include <rlImGui.h>
#include <core/Defines.hpp>
#include "Game.hpp"

namespace Dont_Fall::Test
{
	GuiTest::GuiTest(ImVec2 screenCenter) : screenCenter{ screenCenter }
	{
		rlImGuiSetup(true);
		SetCustomStyle();
	}

	GuiTest::~GuiTest()
	{
		rlImGuiShutdown();
	}

	void GuiTest::RenderStart()
	{
		ImGuiStyle style = ImGui::GetStyle();
		rlImGuiBegin();

		int buttonCount = 4;

		ImVec2 windowSize = { buttonSize.x + style.WindowPadding.x * 2, buttonSize.y * buttonCount };
		windowSize = { windowSize.x,windowSize.y + style.WindowPadding.y * 2 + style.ItemSpacing.x * (buttonCount - 1) };
		Vector2 origin = Utils::GetOrigin(windowSize.x, windowSize.y, Utils::Origin::Center);
		ImVec2 windowPosition = { screenCenter.x - origin.x,screenCenter.y - origin.y };

		ImGui::SetWindowSize("StartMenu", windowSize);
		ImGui::SetWindowPos("StartMenu", windowPosition);

		ImGui::Begin("StartMenu", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

		//for (int i = 0; i < buttonCount; ++i)
		//{
		//	std::string text = "Button " + std::to_string(i + 1);
		//	ImGui::Button(text.c_str(), buttonSize);
		//}

		if (ImGui::Button("Play", buttonSize)) { Game::SetGameState(GameState::Gameplay); }

		if (ImGui::Button("Settings", buttonSize)) { Game::SetGameState(GameState::Gameplay); }

		if (ImGui::Button("Statistics", buttonSize)) { Game::SetGameState(GameState::Gameplay); }

		if (ImGui::Button("Exit", buttonSize)) { Game::SetGameState(GameState::Gameplay); }

		ImGui::End();

		rlImGuiEnd();
	}

	void GuiTest::SetCustomStyle()
	{
		ImGuiStyle& style = ImGui::GetStyle();

		style.WindowPadding = ImVec2(10, 10);
		style.WindowRounding = 4.0f;
		style.FramePadding = ImVec2(6, 6);
		style.FrameRounding = 5.0f;
		style.ItemSpacing = ImVec2(8, 8);
		style.ItemInnerSpacing = ImVec2(4, 4);
		style.IndentSpacing = 20.0f;
		style.ScrollbarSize = 16.0f;
		style.ScrollbarRounding = 8.0f;
		style.GrabMinSize = 8.0f;
		style.GrabRounding = 2.0f;
	}
}