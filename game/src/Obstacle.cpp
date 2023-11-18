#include "Obstacle.hpp"

namespace Dont_Fall
{
	Obstacle::Obstacle(std::string name) : GameObject{ name } {}

	void Obstacle::Draw()
	{
		GameObject::Draw();
	}

	void Obstacle::Start()
	{
		GameObject::Start();

		if (!(spriteComponent = GetComponent<SpriteComponent>())) ERROR("'" + GetName() + "'" + " Doesn't Have A SpriteComponent");
		if (!(rigidbodyComponent = GetComponent<RigidbodyComponent>())) ERROR("'" + GetName() + "'" + " Doesn't Have A RigidbodyComponent");

		rigidbodyComponent->useGravity = false;
		rigidbodyComponent->SetVelocity({ 0,30 });

		GenerateRandomPosition();
	}

	void Obstacle::Update(FrameInfo& frameInfo)
	{
		GameObject::Update(frameInfo);
		transform.rotation += 100 * frameInfo.deltaTime;
	}

	void Obstacle::GenerateRandomPosition()
	{
		transform.position.x = GetRandomValue(0, WIDTH);
		transform.position.y = -spriteComponent->GetTexture().height * transform.scale;
	}
}