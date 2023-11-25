#pragma once

#include <imgui.h>

namespace Test
{
	class GuiTest
	{
	public:
		GuiTest(ImVec2 screenCenter);
		~GuiTest();

		void UpdateStart();
		void RenderStart();

		void UpdateGameOver();
		void RenderGameOver();

		void UpdatePaused();
		void RenderPaused();

		void UpdateGameplay();
		void RenderGameplay();

	private:
		void SetCustomStyle();

		ImVec2 screenCenter{};

		ImVec2 buttonSize{ 200,50 };
		ImVec2 menuPosition{ 200,50 };
	};
}
