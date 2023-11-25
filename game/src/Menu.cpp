#include "Menu.hpp"

namespace RGUI
{
	Menu::Menu(std::string name, ImVec2 position, std::vector<GUIElement*>* elements, Utils::Origin originAnchor) : name{ name }, elements{ elements }
	{
		ImGuiStyle style = ImGui::GetStyle();
		ImVec2 maxSize{};

		for (const auto& button : *elements)
		{
			ImVec2 buttonSize = button->GetSize();
			maxSize.x = std::max(maxSize.x, buttonSize.x);
			maxSize.y += buttonSize.y + style.ItemSpacing.y;
		}

		size.x = maxSize.x + style.WindowPadding.x * 2;
		size.y = maxSize.y + style.WindowPadding.y * 2 - style.ItemSpacing.y;

		Vector2 origin = Utils::GetOrigin(size.x, size.y, originAnchor);
		ImVec2 windowPosition = { position.x - origin.x, position.y - origin.y };
		this->position = windowPosition;
	}

	void Menu::Render()
	{
		ImGui::SetWindowSize(name.c_str(), size);
		ImGui::SetWindowPos(name.c_str(), position);

		ImGui::Begin(name.c_str(), nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

		for (auto button : *elements)
		{
			button->Render();
		}
	}
}