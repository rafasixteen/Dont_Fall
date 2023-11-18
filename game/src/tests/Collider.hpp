#pragma once

#include "../components/Component.hpp"
#include "../core/FrameInfo.hpp"
#include <raylib.h>
#include "../components/SpriteComponent.hpp"

namespace Dont_Fall::Tests
{
	class Collider : public Component
	{
	public:
		enum ColliderType
		{
			Rectangle,
			Circle
		};

		using CollisionCallback = std::function<void(Collider&)>;

		virtual ~Collider();

		virtual void Start() = 0;
		virtual void Update(FrameInfo& frameInfo) = 0;
		virtual void Draw() = 0;

		virtual bool CheckCollision(const Collider& other) = 0;

		void SetCollisionCallback(const CollisionCallback& callback) { collisionCallback = callback; }

		Vector2 origin{};
		bool useSpriteCollider = false;
		bool drawCollider = true;

		CollisionCallback collisionCallback;
		ColliderType colliderType;
		SpriteComponent* spriteComponent;
	};
}