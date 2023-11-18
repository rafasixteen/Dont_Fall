#pragma once

#include "Defines.hpp"

namespace Dont_Fall
{
	class GameObjectMap;

	struct FrameInfo
	{
		float deltaTime;
		GameObjectMap& gameObjects;
	};
}
