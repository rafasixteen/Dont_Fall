#pragma once

#include "Defines.hpp"
#include <raylib.h>
#include <imgui.h>

#define BENCHMARK(code) Utils::Benchmark([&]() { code; })

constexpr int DEFAULT_FONT_SIZE = 32;

namespace Utils
{
	void DrawFrameTime(int posX, int posY, float frameTime);

	void DrawFPS(int posX, int posY, int fps);

	template <typename Func>
	void Benchmark(Func&& func)
	{
		auto start = std::chrono::high_resolution_clock::now();

		std::forward<Func>(func)();

		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

		COLOR_INFO("Time taken by function: " << duration.count() << " microseconds", 96);
	}

	enum Origin
	{
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight,
		Center,
		LeftCenter,
		RightCenter,
		TopCenter,
		BottomCenter
	};
	Vector2 GetOrigin(float width, float height, Origin originAnchor);

	ImVec4 HexToRGBA(const std::string& hex,bool normalize = true);
}
