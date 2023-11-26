#include "RigidbodyComponent.hpp"

RigidbodyComponent::RigidbodyComponent() {}

RigidbodyComponent::~RigidbodyComponent() {}

void RigidbodyComponent::ApplyForce(const Vector2 force)
{
	if (mass <= 0.0f) ERROR("Mass Cannot Be Less Than Or Equal To 0");

	Vector2 acceleration{};
	acceleration.x = force.x ;
	acceleration.y = force.y ;

	velocity = Vector2Add(velocity, acceleration);
}

void RigidbodyComponent::Update(FrameInfo& frameInfo)
{
	if (useGravity) velocity.y += gravityForce * frameInfo.deltaTime ;

	owner->transform.position.x += velocity.x * frameInfo.deltaTime ;
	owner->transform.position.y += velocity.y * frameInfo.deltaTime ;
}
