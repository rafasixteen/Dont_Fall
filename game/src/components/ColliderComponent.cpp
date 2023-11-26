#include "ColliderComponent.hpp"
#include "../GameObjectMap.hpp"
#include "../core/GlobalVariables.hpp"
#include "../Game.hpp"

ColliderComponent::ColliderComponent()
{
	useSpriteCollider = true;
}

ColliderComponent::ColliderComponent(int width, int height)
{
	collider.width = width;
	collider.height = height;
}

void ColliderComponent::Start()
{
	if (!owner) ERROR("Collider doesn't have owner");

	if (useSpriteCollider)
	{
		if (auto spriteComponent = owner->GetComponent<SpriteComponent>())
		{
			collider.width = spriteComponent->GetTexture().width * owner->transform.scale;
			collider.height = spriteComponent->GetTexture().height * owner->transform.scale;
			origin = spriteComponent->GetOrigin();
		}
		else
		{
			ERROR("GameObject doesn't have Sprite Component");
		}
	}

	collider.x = owner->transform.position.x - origin.x;
	collider.y = owner->transform.position.y - origin.y;
}

void ColliderComponent::Update(FrameInfo& frameInfo)
{
	collider.x = owner->transform.position.x - origin.x;
	collider.y = owner->transform.position.y - origin.y;

	for (const auto& [name, gameObject] : frameInfo.gameObjects.GetMap())
	{
		auto otherCollider = gameObject->GetComponent<ColliderComponent>();

		if (otherCollider && otherCollider != this && CheckCollision(*otherCollider))
		{
			if (collisionCallback) collisionCallback(*otherCollider);
			break;
		}
	}
}

void ColliderComponent::Draw()
{
	if (Game::GetGameSettings().gameplaySettings.showHitboxes) DrawRectangleLinesEx(collider, 2, GREEN);
}
