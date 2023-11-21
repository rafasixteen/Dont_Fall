#pragma once

#include "GameObject.hpp"
#include "components/ColliderComponent.hpp"
#include "components/RigidbodyComponent.hpp"

namespace Dont_Fall
{
	class Player : public GameObject
	{
	public:
		Player(std::string name);
		~Player() {}

		void Draw() override;
		void Start() override;
		void Update(FrameInfo& frameInfo) override;

		ColliderComponent* colliderComponent = nullptr;
		RigidbodyComponent* rigidbodyComponent = nullptr;
		void OnCollision(ColliderComponent& otherCollider);

		void Die();
		void Reset();

	private:
		void DrawEyes();

		Vector2 leftEyePosition{};
		Vector2 rightEyePosition{};
		Vector2 offset{};
	};
}
