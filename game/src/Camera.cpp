#include "Camera.hpp"

namespace Dont_Fall
{
	Camera::Camera(Vector2 position)
	{
		handle.target = position;
		handle.offset = position;
		handle.rotation = 0.0f;
		handle.zoom = 1.0f;
	}

	Camera::~Camera()
	{

	}
}
