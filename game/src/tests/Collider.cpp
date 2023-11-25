#include "Collider.hpp"
#include "../GameObject.hpp"
#include "RectangleCollider.hpp"
#include "CircleCollider.hpp"

namespace Tests
{
	Collider::~Collider()
	{

	}

	void Collider::Start()
	{
		if (owner == nullptr) ERROR("Collider doesn't have owner");

		if (useSpriteCollider)
		{
			if (spriteComponent = owner->GetComponent<SpriteComponent>())
			{
				/*switch (colliderType)
				{
				case Tests::Rectangle:
					auto& collider = owner->GetComponent<RectangleCollider>()->collider;
					collider.width = spriteComponent->GetTexture().width * owner->transform.scale;
					collider.height = spriteComponent->GetTexture().height * owner->transform.scale;
					break;
				case Tests::Circle:
					owner->GetComponent<CircleCollider>()->collider.radius = spriteComponent->GetTexture().width * owner->transform.scale / 2;
					break;
				default:
					ERROR("Invalid Collider Type");
				}*/

				origin = spriteComponent->GetOrigin();
			}
			else
			{
				ERROR("GameObject doesn't have Sprite Component");
			}
		}
	}

	void Collider::Draw()
	{

	}

	void Collider::Update(FrameInfo& frameInfo)
	{

	}

	bool Collider::CheckCollision(const Collider& other)
	{
		return false;
	}
}