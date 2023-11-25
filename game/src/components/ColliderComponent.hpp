#pragma once

#include "Component.hpp"
#include <raylib.h>
#include "../GameObject.hpp"
#include "SpriteComponent.hpp"

class ColliderComponent : public Component
{
public:
	using CollisionCallback = std::function<void(ColliderComponent&)>;

	void SetCollisionCallback(const CollisionCallback& callback) { collisionCallback = callback; }

	ColliderComponent();
	ColliderComponent(int width, int height);
	~ColliderComponent() {}

	void Start();
	void Update(FrameInfo& frameInfo);
	void Draw();

	Rectangle GetCollider() const { return collider; }
	bool CheckCollision(const ColliderComponent& other) const { return CheckCollisionRecs(collider, other.collider); }

private:
	Rectangle collider{};
	Vector2 origin{};

	bool useSpriteCollider = false;
	bool drawCollider = true;

	int initialWidth = 0;
	int initialHeight = 0;

	CollisionCallback collisionCallback;

};
