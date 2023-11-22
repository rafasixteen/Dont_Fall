#include "Player.hpp"
#include <raymath.h>
#include "components/ColliderComponent.hpp"
#include "GameObjectMap.hpp"
#include "Ammo.hpp"
#include "core/Utils.hpp"
#include "Gun.hpp"
#include "Obstacle.hpp"
#include "Game.hpp"
#include "Stats.hpp"

namespace Dont_Fall
{
	Player::Player(std::string name) : GameObject{ name } {}

	void Player::Draw()
	{
		GameObject::Draw();
		DrawEyes();
	}

	void Player::Start()
	{
		GameObject::Start();

		if (!(colliderComponent = GetComponent<ColliderComponent>())) ERROR("'" + GetName() + "'" + " Doesn't Have A ColliderComponent");
		if (!(rigidbodyComponent = GetComponent<RigidbodyComponent>())) ERROR("'" + GetName() + "'" + " Doesn't Have A RigidbodyComponent");

		colliderComponent->SetCollisionCallback([this](ColliderComponent& otherCollider) {OnCollision(otherCollider); });
	}

	void Player::Update(FrameInfo& frameInfo)
	{
		GameObject::Update(frameInfo);

		// Eyes //
		Vector2 mousePosition = GetMousePosition();
		float angle = atan2(mousePosition.y - transform.position.y, mousePosition.x - transform.position.x);
		float offsetMagnitude = 2.5f;
		offset = { offsetMagnitude * cos(angle), offsetMagnitude * sin(angle) };

		leftEyePosition = { transform.position.x - 19,transform.position.y - 14 };
		rightEyePosition = { transform.position.x + 5,transform.position.y - 14 };
		// Eyes //

		// Bounds //
		if (transform.position.x < 0) transform.position.x = WIDTH;
		if (transform.position.x > WIDTH) transform.position.x = 0;

		if (transform.position.y < 0) transform.position.y = HEIGHT;
		if (transform.position.y > HEIGHT) transform.position.y = 0;
		// Bounds //
	}

	void Player::DrawEyes()
	{
		DrawCircle(static_cast<int>(leftEyePosition.x + offset.x), static_cast<int>(leftEyePosition.y + offset.y), 5, BLACK);
		DrawCircle(static_cast<int>(rightEyePosition.x + offset.x), static_cast<int>(rightEyePosition.y + offset.y), 5, BLACK);
	}

	void Player::Die()
	{
		auto& playerStats = Stats::GetInstance().GetPlayerStats();
		playerStats.died++;

		Game::ResetGame();
		// TODO: Play Died Sound
		Game::SetGameState(GameState::GameOver);
	}

	void Player::Reset()
	{
		rigidbodyComponent->velocity = { 0,0 };
		transform.position = { WIDTH / 2,HEIGHT / 2 };
	}

	void Player::OnCollision(ColliderComponent& otherCollider)
	{
		auto& otherColliderOwner = *otherCollider.owner;
		if (otherColliderOwner.GetTag() == "Ammo")
		{
			otherColliderOwner.As<Ammo>()->Collect();

			auto& map = GameObjectMap::GetInstance();
			for (auto& [name, ammoObject] : map.GetMap())
			{
				if (ammoObject->GetTag() == "Ammo") ammoObject->As<Ammo>()->GenerateRandomPosition();
			}
		}

		if (otherColliderOwner.GetTag() == "Obstacle")
		{
			Die();
		}
	}
}