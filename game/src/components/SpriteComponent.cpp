#include "SpriteComponent.hpp"
#include "../core/Defines.hpp"
#include "../core/Utils.hpp"
#include "../GameObject.hpp"
#include "../core/GlobalVariables.hpp"

SpriteComponent::SpriteComponent(Texture2D& texture, Utils::Origin originAnchor) : texture{ texture }, originAnchor{ originAnchor }, width{ texture.width }, height{ texture.height } {}

SpriteComponent::~SpriteComponent() { }

void SpriteComponent::Start()
{
	float newWidth = width * owner->transform.scale;
	float newHeight = height * owner->transform.scale;

	origin = Utils::GetOrigin(newWidth, newHeight, originAnchor);
}

void SpriteComponent::Draw()
{
	Vector2 ratio = Core::GlobalVariables::ratio;

	float newWidth = width * owner->transform.scale;
	float newHeight = height * owner->transform.scale;
	origin = Utils::GetOrigin(newWidth * ratio.x, newHeight * ratio.y, originAnchor);

	auto transform = owner->transform;
	Rectangle sourceRec = { 0.0f, 0.0f, width, height };
	Rectangle destRec = { transform.position.x , transform.position.y , width * transform.scale * ratio.x, height * transform.scale * ratio.y };

	DrawTexturePro(texture, sourceRec, destRec, origin, transform.rotation, WHITE);
}
