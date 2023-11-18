#include "guiTest.hpp"

#include <rlImGui.h>
#include <imgui.h>
#include <core/Defines.hpp>

namespace Dont_Fall::Test
{
	GuiTest::GuiTest()
	{
		rlImGuiSetup(true);
	}

	GuiTest::~GuiTest()
	{
		rlImGuiShutdown();
	}

	void GuiTest::Render()
	{
		rlImGuiBegin();

		ImGui::Text("Hello, ImGui!");
		
		if (ImGui::Button("Click me!"))
		{
			INFO("Clicked");
		}

		rlImGuiEnd();
	}
}