#pragma once

#include "core/Defines.hpp"

namespace Dont_Fall
{
	class Window
	{
	public:
		Window(const int width, const int height);
		~Window();

	private:
		const char* windowName = "Don't Fall";
	};
}