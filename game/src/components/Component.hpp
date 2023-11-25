#pragma once

#include "../core/Defines.hpp"

class GameObject;

class Component
{
public:
	virtual ~Component() {}
	GameObject* owner = nullptr;
};
