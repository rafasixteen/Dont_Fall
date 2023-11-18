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

namespace Dont_Fall
{
	GameState Game::currentGameState = GameState::Start;

	Game::Game()
	{
		SetExitKey(KEY_NULL);
		//SetTargetFPS(60);

		LoadAssets();
		LoadGameObjects();
	}

	Game::~Game()
	{
		UnloadAssets();
	}

	void Game::Run()
	{
		Start();

		while (!WindowShouldClose())
		{
			deltaTime = GetFrameTime();
			fps = GetFPS();

			FrameInfo frameInfo{deltaTime, gameObjects};

			Update(frameInfo);
			Draw();
		}
	}

	void Game::Draw()
	{
		BeginDrawing();
		ClearBackground(LIGHTGRAY);

		Utils::DrawFPS(0, 0, fps);
		Utils::DrawFrameTime(0, 20, deltaTime);

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
		default:
			ERROR("Invalid GameState");
		}
		guiTest.Render();
		EndDrawing();
	}

	void Game::Update(FrameInfo& frameInfo)
	{
		switch (currentGameState)
		{
		case GameState::Start:
			gui.UpdateStart();
			break;
		case GameState::Gameplay:
			if (IsKeyPressed(KEY_ESCAPE)) { Game::SetGameState(GameState::Paused); }
			gameObjects.Update(frameInfo);
			gui.UpdateGameplay();
			break;
		case GameState::GameOver:
			gui.UpdateGameOver();
			break;
		case GameState::Paused:
			if (IsKeyPressed(KEY_ESCAPE)) { Game::SetGameState(GameState::Gameplay); }
			gui.UpdatePaused();
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
		for (int i = 0; i < AMMO_COUNT; ++i)
		{
			auto ammoGameObject = std::make_unique<Ammo>("Ammo" + std::to_string(i + 1));
			ammoGameObject->SetTag("Ammo");
			ammoGameObject->AddComponent(std::make_unique<SpriteComponent>(textures["Ammo"], Utils::Origin::Center));
			ammoGameObject->AddComponent(std::make_unique<ColliderComponent>());
			ammoGameObject->transform.scale = 0.15f;
			gameObjects.Add(std::move(ammoGameObject));
		}

		for (int i = 0; i < OBSTACLES_COUNT; ++i)
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
		playerGameObject->transform.position = screenCenter;
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
}