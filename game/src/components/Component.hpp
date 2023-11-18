#pragma once

#include "../core/Defines.hpp"

namespace Dont_Fall
{
	class GameObject;

	class Component
	{
	public:
		virtual ~Component() {}
		GameObject* owner = nullptr;
	};
}