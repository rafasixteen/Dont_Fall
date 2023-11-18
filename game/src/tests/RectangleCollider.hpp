#pragma once

#include "Collider.hpp"
#include <raylib.h>

namespace Dont_Fall::Tests
{
	class RectangleCollider : public Collider
	{
	public:
		RectangleCollider();
		~RectangleCollider();

		void Start() override;
		void Update(FrameInfo& frameInfo) override;
		void Draw() override;

		bool CheckCollision(const Collider& other) override;

		::Rectangle collider;
	};
}