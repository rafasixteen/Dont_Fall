#pragma once

#include "Collider.hpp"
#include <raylib.h>

namespace Tests
{
	struct Circlee
	{
		int x;
		int y;
		float radius;
		Color color;
	};

	class CircleCollider : public Collider
	{

	public:
		//CircleCollider();
		//CircleCollider(float radius);
		//~CircleCollider();

		//void Start() override;
		//void Update(FrameInfo& frameInfo) override;
		//void Draw() override;

		Circlee collider{};
	};
}