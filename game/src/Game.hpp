#pragma once

#include "Window.hpp"
#include "GameObjectMap.hpp"
#include "core/Defines.hpp"
#include "core/FrameInfo.hpp"
#include "gui/GUI.hpp"
#include <Stats.hpp>

namespace Dont_Fall
{
	enum GameState
	{
		Start,
		Gameplay,
		GameOver,
		Paused,
		Settings,
		Statistics
	};

	class Game
	{
	public:
		Game();
		~Game();

		void Run();

		static void SetGameState(GameState newState) { currentGameState = newState; }
		static GameState GetGameState() { return currentGameState; }
		Vector2 GetScreenCenter() const { return screenCenter; }
		static void ResetGame();
		static void StartGame();

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
		RGUI::GUI gui{ {screenCenter.x,screenCenter.y} };

		GameObjectMap& gameObjects = GameObjectMap::GetInstance();
		Stats& stats = Stats::GetInstance();

		std::unordered_map<std::string, Texture2D> textures;

		float deltaTime = 0.0f;
		int fps = 0;;
	};
}