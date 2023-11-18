#include "RectangleCollider.hpp"
#include "../GameObjectMap.hpp"

namespace Dont_Fall::Tests
{
	RectangleCollider::RectangleCollider()
	{
		useSpriteCollider = true;
	}

	RectangleCollider::~RectangleCollider()
	{

	}

	void RectangleCollider::Start()
	{
		Collider::Start();

		collider.width = spriteComponent->GetTexture().width * owner->transform.scale;
		collider.height = spriteComponent->GetTexture().height * owner->transform.scale;
	}

	void RectangleCollider::Update(FrameInfo& frameInfo)
	{
		Collider::Update(frameInfo);

		collider.x = owner->transform.position.x - origin.x;
		collider.y = owner->transform.position.y - origin.y;
	}

	void RectangleCollider::Draw()
	{
		if (drawCollider) DrawRectangleLinesEx(collider, 2, GREEN);
	}

	bool RectangleCollider::CheckCollision(const Collider& other)
	{
		auto& otherCollider = *other.owner->GetComponent<RectangleCollider>();
		switch (other.colliderType)
		{
		case 0: 
			break;
		case 1:
			break;
		default:
			break;
		}

		//return CheckCollisionRecs(collider, other.co);
		return true;
	}
}