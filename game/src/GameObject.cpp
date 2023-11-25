#include "GameObject.hpp"
#include "components/SpriteComponent.hpp"
#include "components/RigidbodyComponent.hpp"
#include "components/ColliderComponent.hpp"

GameObject::GameObject(std::string name) : name{ name }
{
}

GameObject::~GameObject()
{
}

void GameObject::AddChild(GameObject& child)
{
	child.parent = this;
	children.push_back(&child);
}

GameObject& GameObject::GetChild(std::string name)
{
	for (GameObject* child : children)
	{
		if (child->GetName() == name)
		{
			return *child;
		}
	}
	ERROR("Child is Either Nullptr or '" + name + "' is an Invalid Child Name");
	throw std::runtime_error("");
}

void GameObject::Draw()
{
	if (auto spriteComponent = GetComponent<SpriteComponent>())
	{
		spriteComponent->Draw();
	}

	if (auto colliderComponent = GetComponent<ColliderComponent>())
	{
		colliderComponent->Draw();
	}
}

void GameObject::Start()
{
	if (auto spriteComponent = GetComponent<SpriteComponent>())
	{
		spriteComponent->Start();
	}

	if (auto colliderComponent = GetComponent<ColliderComponent>())
	{
		colliderComponent->Start();
	}
}

void GameObject::Update(FrameInfo& frameInfo)
{
	if (auto rigidbodyComponent = GetComponent<RigidbodyComponent>())
	{
		rigidbodyComponent->Update(frameInfo);
	}

	if (auto colliderComponent = GetComponent<ColliderComponent>())
	{
		colliderComponent->Update(frameInfo);
	}

	for (auto& child : children)
	{
		child->transform.position.x = this->transform.position.x;
		child->transform.position.y = this->transform.position.y;
	}
}

