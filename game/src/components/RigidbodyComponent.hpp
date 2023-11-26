#pragma once

#include <raylib.h>
#include "Component.hpp"
#include "../GameObject.hpp"
#include "core/GlobalVariables.hpp"
#include <raymath.h>

class RigidbodyComponent : public Component
{
public:
	RigidbodyComponent();
	~RigidbodyComponent();

	void Update(FrameInfo& frameInfo);

	void ApplyForce(const Vector2 force);
	void SetVelocity(const Vector2 velocity) { this->velocity = velocity; }

	Vector2 velocity{};
	float mass = 1.0f;
	bool useGravity = true;
	const float gravityForce = 9.8f * 50.0f;
};
