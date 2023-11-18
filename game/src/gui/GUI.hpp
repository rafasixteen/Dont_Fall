#pragma once

#include <raylib.h>
#include "Button.hpp"
#include "Label.hpp"

namespace Dont_Fall::RGUI
{
	class GUI
	{
	public:
		GUI(Vector2 screenCenter);
		~GUI();

		void UpdateStart();
		void RenderStart();

		void UpdateGameOver();
		void RenderGameOver();

		void UpdatePaused();
		void RenderPaused();

		void UpdateGameplay();
		void RenderGameplay();
	private:
		void DrawAmmoCount();

		Vector2 screenCenter{};

		Button startButton{ {screenCenter.x,screenCenter.y,200,50},"Start" };
		Button restartButton{ {screenCenter.x,screenCenter.y,200,50},"Restart" };
		Button resumeButton{ {screenCenter.x,screenCenter.y,200,50},"Resume" };

		Label ammoLabel{ screenCenter,100,0,BLACK,"Assets/Fonts/Roboto/Roboto-Medium.ttf" };
	};
}