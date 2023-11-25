#pragma once

#include "Defines.hpp"

class GameObjectMap;

struct FrameInfo
{
	float deltaTime;
	GameObjectMap& gameObjects;

	int currentWidth;
	int currentHeight;
};

