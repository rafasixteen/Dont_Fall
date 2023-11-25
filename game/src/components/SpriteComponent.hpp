#pragma once

#include <raylib.h>

#include "Component.hpp"
#include "../core/Utils.hpp"

class SpriteComponent : public Component
{
public:
	SpriteComponent(Texture2D& texture, Utils::Origin originAnchor);
	~SpriteComponent();

	Texture2D& GetTexture() { return texture; }
	Vector2 GetOrigin() const { return origin; }

	void Start();
	void Draw();

private:
	Texture2D& texture;
	int width;
	int height;

	Utils::Origin originAnchor;
	Vector2 origin{};
};
