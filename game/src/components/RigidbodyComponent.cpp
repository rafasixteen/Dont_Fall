#include "RigidbodyComponent.hpp"

RigidbodyComponent::RigidbodyComponent() {}

RigidbodyComponent::~RigidbodyComponent() {}

void RigidbodyComponent::ApplyForce(const Vector2 force)
{
	if (mass <= 0.0f) ERROR("Mass Cannot Be Less Than Or Equal To 0");
	
	ratio = Core::GlobalVariables::ratio;

	Vector2 acceleration{};
	acceleration.x = force.x * ratio.x;
	acceleration.y = force.y * ratio.y;

	velocity = Vector2Add(velocity, acceleration);
}

void RigidbodyComponent::Update(FrameInfo& frameInfo)
{
	if (useGravity) velocity.y += gravityForce * frameInfo.deltaTime * ratio.y;

	owner->transform.position.x += velocity.x * frameInfo.deltaTime * ratio.x;
	owner->transform.position.y += velocity.y * frameInfo.deltaTime * ratio.y;
}
