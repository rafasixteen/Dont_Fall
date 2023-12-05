#include "Menu.hpp"
#include "core/GlobalVariables.hpp"

namespace RGUI
{
	void Menu::Render()
	{
		ImGui::Begin(name.c_str(), nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground);

		ImVec2 size = { static_cast<float>(Core::GlobalVariables::currentWidth),static_cast<float>(Core::GlobalVariables::currentHeight) };
		ImGui::SetWindowSize(name.c_str(), size);
		ImGui::SetWindowPos(name.c_str(), { 0,0 });

		float yPos = ImGui::GetCursorPosY();
		yPos += Core::GlobalVariables::currentHeight / 2.0f;
		yPos -= elements->at(0)->GetSize().y / 2.0f;
		yPos -= elements->at(0)->GetSize().y * 2.0f;

		ImGui::SetCursorPosY(yPos);
		for (auto button : *elements)
		{
			float xPos = ImGui::GetCursorPosX() + Core::GlobalVariables::currentWidth / 2.0f - button->GetSize().x / 2.0f - ImGui::GetStyle().WindowPadding.x;
			ImGui::SetCursorPosX(xPos);
			button->Render();
		}

		ImGui::End();
	}
}