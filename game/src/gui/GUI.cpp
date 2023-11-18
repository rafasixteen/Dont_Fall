#include "GUI.hpp"
#include "../Game.hpp"
#include "../Gun.hpp"

namespace Dont_Fall::RGUI
{
	GUI::GUI(Vector2 screenCenter) : screenCenter{ screenCenter }
	{

	}

	GUI::~GUI()
	{

	}

	//---------------------------------------------------------------------------------------------//

	void GUI::UpdateStart()
	{
		if (startButton.IsClicked())
		{
			Game::SetGameState(Dont_Fall::Gameplay);
		}
	}

	void GUI::RenderStart()
	{
		startButton.Render();

	}

	//---------------------------------------------------------------------------------------------//

	void GUI::UpdateGameOver()
	{
		if (restartButton.IsClicked())
		{
			Game::SetGameState(Dont_Fall::Gameplay);
		}
	}

	void GUI::RenderGameOver()
	{
		restartButton.Render();
	}

	//---------------------------------------------------------------------------------------------//

	void GUI::UpdatePaused()
	{
		if (resumeButton.IsClicked())
		{
			Game::SetGameState(Dont_Fall::Gameplay);
		}
	}

	void GUI::RenderPaused()
	{
		resumeButton.Render();
	}

	//---------------------------------------------------------------------------------------------//

	void GUI::UpdateGameplay()
	{

	}

	void GUI::RenderGameplay()
	{
		DrawAmmoCount();
	}

	//---------------------------------------------------------------------------------------------//

	void GUI::DrawAmmoCount()
	{
		auto& map = GameObjectMap::GetInstance();
		int& ammoCount = map.FindByName("Gun").As<Gun>()->ammoCount;
		ammoLabel.Render(std::to_string(ammoCount).c_str());
	}
}