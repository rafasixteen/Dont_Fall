#include "Game.hpp"
#include "Player.hpp"
#include "Gun.hpp"
#include "Ammo.hpp"
#include "Obstacle.hpp"
#include "core/Utils.hpp"
#include "components/SpriteComponent.hpp"
#include "components/RigidbodyComponent.hpp"
#include "components/ColliderComponent.hpp"

#include <raylib.h>

GameState Game::currentGameState = GameState::Start;
GameSettings Game::gameSettings;

Game::Game()
{
	SetExitKey(KEY_NULL);
	//SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
	InitAudioDevice();
	SetMasterVolume(gameSettings.audioSettings.masterVolume / 100.0f);

	LoadAssets();
	LoadGameObjects();
}

Game::~Game()
{
	CloseAudioDevice();
	UnloadAssets();
}

void Game::Run()
{
	Start();

	while (!WindowShouldClose())
	{
		deltaTime = GetFrameTime();
		fps = GetFPS();

		if (IsWindowResized())
		{
			Core::GlobalVariables::UpdateGlobals();
		}

		FrameInfo frameInfo{ deltaTime, gameObjects,Core::GlobalVariables::currentWidth,Core::GlobalVariables::currentHeight };

		Update(frameInfo);
		Draw();
	}
}

void Game::Draw()
{
	BeginDrawing();
	ClearBackground(LIGHTGRAY);

	switch (currentGameState)
	{
	case GameState::Start:
		gui.RenderStart();
		break;
	case GameState::Gameplay:
		gui.RenderGameplay();
		gameObjects.Draw();
		break;
	case GameState::GameOver:
		gui.RenderGameOver();
		break;
	case GameState::Paused:
		gameObjects.Draw();
		gui.RenderPaused();
		break;
	case GameState::Settings:
		gui.RenderSettings();
		break;
	case GameState::Statistics:
		gui.RenderStatistics();
		break;
	default:
		ERROR("Invalid GameState");
	}
	EndDrawing();
}

void Game::Update(FrameInfo& frameInfo)
{
	switch (currentGameState)
	{
	case GameState::Start:
		audioManager.PlayMusic("Menu");
		gui.UpdateStart();
		break;
	case GameState::Gameplay:
		gameObjects.Update(frameInfo);
		audioManager.PlayMusic("Gameplay");
		gui.UpdateGameplay();
		break;
	case GameState::GameOver:
		gui.UpdateGameOver();
		break;
	case GameState::Paused:
		gui.UpdatePaused();
		break;
	case GameState::Settings:
		gui.UpdateSettings();
		break;
	case GameState::Statistics:
		gui.UpdateStatistics();
		break;
	default:
		ERROR("Invalid GameState");
	}
}

void Game::Start()
{
	gameObjects.Start();
}

void Game::LoadGameObjects()
{
	for (int i = 0; i < 3; ++i)
	{
		auto ammoGameObject = std::make_unique<Ammo>("Ammo" + std::to_string(i + 1));
		ammoGameObject->SetTag("Ammo");
		ammoGameObject->AddComponent(std::make_unique<SpriteComponent>(textures["Ammo"], Utils::Origin::Center));
		ammoGameObject->AddComponent(std::make_unique<ColliderComponent>());
		ammoGameObject->transform.scale = 0.15f;
		gameObjects.Add(std::move(ammoGameObject));
	}

	for (int i = 0; i < 3; ++i)
	{
		auto obstacleGameObject = std::make_unique<Obstacle>("Obstacle" + std::to_string(i + 1));
		obstacleGameObject->SetTag("Obstacle");
		obstacleGameObject->AddComponent(std::make_unique<SpriteComponent>(textures["Saw"], Utils::Origin::Center));
		obstacleGameObject->AddComponent(std::make_unique<ColliderComponent>());
		obstacleGameObject->AddComponent(std::make_unique<RigidbodyComponent>());
		obstacleGameObject->transform.scale = 0.5f;
		gameObjects.Add(std::move(obstacleGameObject));
	}

	auto gunGameObject = std::make_unique<Gun>("Gun");
	gunGameObject->AddComponent(std::make_unique<SpriteComponent>(textures["Gun"], Utils::Origin::LeftCenter));
	gunGameObject->transform.scale = 0.5f;
	gameObjects.Add(std::move(gunGameObject));

	auto playerGameObject = std::make_unique<Player>("Player");
	playerGameObject->AddComponent(std::make_unique<SpriteComponent>(textures["Player"], Utils::Origin::Center));
	playerGameObject->AddComponent(std::make_unique<RigidbodyComponent>());
	playerGameObject->AddComponent(std::make_unique<ColliderComponent>());
	playerGameObject->AddChild(gameObjects.FindByName("Gun"));
	playerGameObject->transform.scale = 0.25f;
	playerGameObject->transform.position = Core::GlobalVariables::screenCenter;
	gameObjects.Add(std::move(playerGameObject));
}

void Game::LoadAssets()
{
	Texture2D playerTexture = LoadTexture("Assets/Sprites/Player.png");
	textures.emplace("Player", std::move(playerTexture));

	Texture2D gunTexture = LoadTexture("Assets/Sprites/Gun.png");
	textures.emplace("Gun", std::move(gunTexture));

	Texture2D ammoTexture = LoadTexture("Assets/Sprites/Ammo.png");
	textures.emplace("Ammo", std::move(ammoTexture));

	Texture2D sawTexture = LoadTexture("Assets/Sprites/Saw.png");
	textures.emplace("Saw", std::move(sawTexture));

	auto& audioManager = AudioManager::GetInstance();
	audioManager.LoadAudio("Shoot", "Assets/Audio/Shoot.wav");
	audioManager.LoadAudio("CantShoot", "Assets/Audio/CantShoot.wav");
	audioManager.LoadAudio("Died", "Assets/Audio/Died.wav");
	audioManager.LoadAudio("Reload", "Assets/Audio/Reload.wav");
	audioManager.LoadAudio("Spawn", "Assets/Audio/Spawn.wav");

	audioManager.LoadMusic("Gameplay", "Assets/Music/Gameplay.mp3");
	//audioManager.LoadMusic("Menu", "Assets/Music/Cipher2.mp3");
	audioManager.LoadMusic("Menu", "Assets/Music/Space-Jazz.mp3");
}

void Game::UnloadAssets()
{
	for (const auto& [name, texture] : textures)
	{
		UnloadTexture(texture);
	}

	textures.clear();
	gameObjects.Clear();
}

void Game::ResetGame()
{
	Stats::GetInstance().ResumeTimer();
	Stats::GetInstance().StopTimer();

	auto& map = GameObjectMap::GetInstance();
	map.FindByName("Gun").As<Gun>()->ammoCount = 5;
	map.FindByName("Player").As<Player>()->Reset();

	for (auto& [name, ammoObject] : map.GetMap())
	{
		if (ammoObject->GetTag() == "Ammo") ammoObject->As<Ammo>()->GenerateRandomPosition();
	}

	for (auto& [name, obstacleObject] : map.GetMap())
	{
		if (obstacleObject->GetTag() == "Obstacle") obstacleObject->As<Obstacle>()->GenerateRandomPosition();
	}

	auto& playerStats = Stats::GetInstance().GetPlayerStats();
	playerStats.time = Stats::GetInstance().GetTime();
	Stats::GetInstance().SaveStatsToFile("stats.txt");
}

void Game::StartGame()
{
	auto& playerStats = Stats::GetInstance().GetPlayerStats();
	playerStats.gamesPlayed++;

	Stats::GetInstance().StartTimer();
	AudioManager::GetInstance().Play("Spawn");
	SetGameState(GameState::Gameplay);
}
