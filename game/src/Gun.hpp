#pragma once

#include "GameObject.hpp"

class Gun : public GameObject
{
public:
	Gun(std::string name);
	~Gun() {}

	void Draw() override;
	void Start() override;
	void Update(FrameInfo& frameInfo) override;

	void Fire();

	int ammoCount = 0;
};
