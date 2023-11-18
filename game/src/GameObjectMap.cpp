#include "GameObjectMap.hpp"

namespace Dont_Fall
{
	GameObjectMap GameObjectMap::instance;
	GameObjectMap::GameObjectMap() {}

	GameObjectMap& GameObjectMap::GetInstance()
	{
		return instance;
	}

	// Linear Search O(N)
	GameObject& GameObjectMap::FindByTag(const std::string& tag)
	{
		auto it = std::find_if(gameObjects.begin(), gameObjects.end(),
			[&tag](const auto& pair) { return pair.second->GetTag() == tag; });

		if (it != gameObjects.end())
		{
			return *it->second;
		}

		ERROR("Game object with tag '" + tag + "' not found.");
		throw std::runtime_error("");
	}

	// Constant Search O(1)
	GameObject& GameObjectMap::FindByName(const std::string& name)
	{
		auto& obj = gameObjects[name];
		if (obj == nullptr)
		{
			ERROR("Game object with name '" + name + "' not found.");
			throw std::runtime_error("");
		}
		else
		{
			return *obj;
		}
	}

	void GameObjectMap::Add(std::unique_ptr<GameObject> gameObject)
	{
		gameObjects.emplace(gameObject->GetName(), std::move(gameObject));
	}

	void GameObjectMap::Draw()
	{
		for (const auto& [name, gameObject] : gameObjects)
		{
			gameObject->Draw();
		}
	}

	void GameObjectMap::Start()
	{
		for (const auto& [name, gameObject] : gameObjects)
		{
			gameObject->Start();
		}
	}

	void GameObjectMap::Update(FrameInfo& frameInfo)
	{
		for (const auto& [name, gameObject] : gameObjects)
		{
			gameObject->Update(frameInfo);
		}
	}
}