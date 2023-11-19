#pragma once

#include <raylib.h>
#include <rcamera.h>

namespace Dont_Fall
{
	class Camera
	{
	public:
		Camera(Vector2 position);
		~Camera();

		Camera2D GetHandle() const { return handle; }
		void SetPosition(Vector2 position) { handle.target = position; }
		void SetOffset(Vector2 offset) { handle.offset = offset; }

		void AddPosition(Vector2 position) { handle.target.x += position.x, handle.target.y += position.y; }
		void AddOffset(Vector2 offset) { handle.offset.x += offset.x, handle.offset.y += offset.y; }

	private:
		Camera2D handle;
	};
}