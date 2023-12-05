#include "Obstacle.hpp"
#include "core/GlobalVariables.hpp"
#include "GameObjectMap.hpp"

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

	if (transform.position.y > frameInfo.currentHeight) GenerateRandomPosition();
}

void Obstacle::GenerateRandomPosition()
{
	std::vector<Vector2> obstaclePositions;

	for (auto& [name, obstacle] : GameObjectMap::GetInstance().GetMap())
	{
		if (obstacle->GetTag() == "Obstacle" && obstacle.get() != this)
		{
			obstaclePositions.push_back(obstacle->transform.position);
		}
	}

	const float minDistance = spriteComponent->GetTexture().width + 20.0f;
	bool validPosition = true;
	do
	{
		transform.position.x = GetRandomValue(0, Core::GlobalVariables::currentWidth);
		transform.position.y = 0;

		validPosition = true;
		for (const auto& position : obstaclePositions)
		{
			float distance = Vector2Distance(transform.position, position);
			if (distance < minDistance)
			{
				validPosition = false;
				break;
			}
		}
	} while (!validPosition);
}
