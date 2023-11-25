#pragma once

#include "Window.hpp"
#include "GameObjectMap.hpp"
#include "core/Defines.hpp"
#include "core/FrameInfo.hpp"
#include "gui/GUI.hpp"
#include <Stats.hpp>
#include "core/GameSettings.hpp"
#include "core/GlobalVariables.hpp"

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
	static GameSettings& GetGameSettings() { return gameSettings; }

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
	static GameSettings gameSettings;

	Window window{ Core::GlobalVariables::initialWidth,Core::GlobalVariables::initialHeight };
	RGUI::GUI gui{};

	GameObjectMap& gameObjects = GameObjectMap::GetInstance();
	Stats& stats = Stats::GetInstance();

	std::unordered_map<std::string, Texture2D> textures;

	float deltaTime = 0.0f;
	int fps = 0;;
};
