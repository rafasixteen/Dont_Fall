#pragma once

#include "Window.hpp"
#include "GameObjectMap.hpp"
#include "core/Defines.hpp"
#include "core/FrameInfo.hpp"
#include "gui/GUI.hpp"
#include "tests/guiTest/guiTest.hpp"

namespace Dont_Fall
{
	enum GameState
	{
		Start,
		Gameplay,
		GameOver,
		Paused
	};

	class Game
	{
	public:
		Game();
		~Game();

		void Run();

		static void SetGameState(GameState newState) { currentGameState = newState; }
		static GameState GetGameState() { return currentGameState; }

	private:
		void Start();
		void Update(FrameInfo& frameInfo);
		void Draw();

		void LoadGameObjects();
		void LoadAssets();
		void UnloadAssets();

		static GameState currentGameState;

		const Vector2 screenCenter = { static_cast<float>(WIDTH) / 2, static_cast<float>(HEIGHT) / 2 };
		const int AMMO_COUNT = 3;
		const int OBSTACLES_COUNT = 3;

		Window window{ WIDTH,HEIGHT };
		RGUI::GUI gui{ screenCenter };
		Test::GuiTest guiTest{};

		GameObjectMap& gameObjects = GameObjectMap::GetInstance();
		std::unordered_map<std::string, Texture2D> textures;

		float deltaTime = 0.0f;
		int fps = 0;
	};
}