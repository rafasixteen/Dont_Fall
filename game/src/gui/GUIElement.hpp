#pragma once

namespace RGUI
{
	class GUIElement
	{
	public:
		virtual ~GUIElement() = default;
		virtual void Render() = 0;

		virtual ImVec2 GetSize() const = 0;

		template <typename T>
		T* As()
		{
			return dynamic_cast<T*>(this);
		}
	};
}