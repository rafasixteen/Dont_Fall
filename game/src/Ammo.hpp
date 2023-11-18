#pragma once

#include "GameObject.hpp"
#include "ICollectible.hpp"

namespace Dont_Fall
{
	class Ammo : public GameObject, public ICollectible
	{
	public:
		Ammo(std::string name);
		~Ammo() {}

		void Draw() override;
		void Start() override;
		void Update(FrameInfo &frameInfo) override;

		void Collect() const override;

		void GenerateRandomPosition();
	};
}