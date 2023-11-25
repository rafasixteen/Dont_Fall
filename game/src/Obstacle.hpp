#pragma once

#include "GameObject.hpp"
#include "components/RigidbodyComponent.hpp"
#include "components/SpriteComponent.hpp"

class Obstacle : public GameObject
{
public:
	Obstacle(std::string name);
	~Obstacle() {}

	void Draw() override;
	void Start() override;
	void Update(FrameInfo& frameInfo) override;

	void GenerateRandomPosition();

private:
	RigidbodyComponent* rigidbodyComponent = nullptr;
	SpriteComponent* spriteComponent = nullptr;
};
