#include "Ammo.hpp"
#include "core/Defines.hpp"
#include "GameObjectMap.hpp"
#include "Gun.hpp"
#include "Stats.hpp"

namespace Dont_Fall
{
	Ammo::Ammo(std::string name) : GameObject{ name } {}

	void Ammo::Draw()
	{
		GameObject::Draw();
	}

	void Ammo::Start()
	{
		GameObject::Start();
		GenerateRandomPosition();
	}

	void Ammo::Update(FrameInfo& frameInfo)
	{
		GameObject::Update(frameInfo);
	}

	void Ammo::Collect() const
	{
		auto& map = GameObjectMap::GetInstance().GetMap();
		map["Gun"]->As<Gun>()->ammoCount++;
		Stats::GetInstance().GetPlayerStats().ammoCollected++;
	}

	void Ammo::GenerateRandomPosition()
	{
		transform.position.x = GetRandomValue(0, WIDTH);
		transform.position.y = GetRandomValue(0, HEIGHT);
	}
}