//#include "CircleColliderComponent.hpp"
//
//namespace Dont_Fall
//{
//	CircleColliderComponent::CircleColliderComponent()
//	{
//		collider.color = GREEN;
//		useSpriteCollider = true;
//	}
//
//	CircleColliderComponent::CircleColliderComponent(float radius)
//	{
//		collider.radius = radius;
//		collider.color = GREEN;
//	}
//
//	CircleColliderComponent::~CircleColliderComponent()
//	{
//
//	}
//
//	void CircleColliderComponent::Start()
//	{
//		CircleColliderComponent::Start();
//	}
//
//	void CircleColliderComponent::Update(FrameInfo& frameInfo)
//	{
//		CircleColliderComponent::Update(frameInfo);
//
//		collider.x = owner->transform.position.x - origin.x;
//		collider.y = owner->transform.position.y - origin.y;
//	}
//
//	void CircleColliderComponent::Draw()
//	{
//		if (drawCollider) DrawCircleLines(collider.x, collider.y, collider.radius, collider.color);
//	}
//}