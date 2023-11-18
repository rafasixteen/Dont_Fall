#include "Gun.hpp"
#include <raymath.h>
#include "components/RigidbodyComponent.hpp"

namespace Dont_Fall
{
	Gun::Gun(std::string name) : GameObject{ name } {}

	void Gun::Draw()
	{
		GameObject::Draw();
	}

	void Gun::Start()
	{
		GameObject::Start();
		ammoCount = 5;
	}

	void Gun::Update(FrameInfo& frameInfo)
	{
		GameObject::Update(frameInfo);

		// Gun Rotation //
		Vector2 mousePosition = GetMousePosition();
		Vector2 direction = Vector2Subtract(mousePosition, transform.position);
		float angle = atan2(direction.y, direction.x) * RAD2DEG;
		transform.rotation = angle;
		// Gun Rotation //

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			Fire();
		}
	}

	void Gun::Fire()
	{
		if (parent == nullptr)
		{
			WARNING("Assign a Parent To The Gun GameObject For It To Work");
			return;
		}

		if (ammoCount <= 0) return;
		ammoCount--;

		auto playerRigidbody = parent->GetComponent<RigidbodyComponent>();

		float oppositeAngle = transform.rotation + 180.0f;
		Vector2 force = Vector2Rotate({ 10.0f, 0.0f }, DEG2RAD * oppositeAngle);
		int magnitude = 75;

		playerRigidbody->SetVelocity({ force.x * magnitude,force.y * magnitude });
	}
}