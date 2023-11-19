#pragma once

#include "core/Defines.hpp"
#include "GameObject.hpp"
#include "core/FrameInfo.hpp"

namespace Dont_Fall
{
	class GameObjectMap
	{
	public:
		static GameObjectMap& GetInstance();

		GameObject& FindByTag(const std::string& tag);
		GameObject& FindByName(const std::string& name);

		void Add(std::unique_ptr<GameObject> gameObject);
		void Clear() { gameObjects.clear(); }

		std::unordered_map<std::string, std::unique_ptr<GameObject>>& GetMap() { return gameObjects; }

		void Draw();
		void Start();
		void Update(FrameInfo& frameInfo);

	private:
		GameObjectMap();

		static GameObjectMap instance;
		std::unordered_map<std::string, std::unique_ptr<GameObject>> gameObjects;
	};
}