#pragma once

#include <raylib.h>
#include "components/Component.hpp"
#include "core/Defines.hpp"
#include "core/FrameInfo.hpp"

class GameObject
{
	struct Transform
	{
		Vector2 position{};
		float rotation = 0.0f;
		float scale = 1.0f;
	};

public:
	GameObject(std::string name);
	~GameObject();

	virtual void Draw() = 0;
	virtual void Start() = 0;
	virtual void Update(FrameInfo& frameInfo) = 0;

	std::string GetName() const { return name; }
	void SeName(std::string name) { this->name = name; }
	std::string GetTag() const { return tag; }
	void SetTag(std::string tag) { this->tag = tag; }

	template <typename T>
	T* As()
	{
		return dynamic_cast<T*>(this);
	}

	template <typename T>
	T* AddComponent(std::unique_ptr<T> component)
	{
		component->owner = this;
		components[typeid(T)] = std::move(component);
		return static_cast<T*>(components[typeid(T)].get());
	}

	template <typename T>
	T* GetComponent()
	{
		auto it = components.find(typeid(T));
		if (it != components.end())
		{
			return static_cast<T*>(it->second.get());
		}
		return nullptr;
	}

	void AddChild(GameObject& child);
	GameObject& GetChild(std::string name);

	Transform transform;
	GameObject* parent = nullptr;
private:
	std::string name;
	std::string tag;
	std::unordered_map<std::type_index, std::unique_ptr<Component>> components;
	std::vector<GameObject*> children;
};

