#include "Stats.hpp"

namespace Dont_Fall
{
	void Stats::StartTimer()
	{
		start = std::chrono::high_resolution_clock::now();
		paused = false;
	}

	void Stats::StopTimer()
	{
		stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		time = duration.count();
	}

	void Stats::PauseTimer()
	{
		if (!paused)
		{
			pauseStart = std::chrono::high_resolution_clock::now();
			paused = true;
		}
	}

	void Stats::ResumeTimer()
	{
		if (paused)
		{
			auto pauseEnd = std::chrono::high_resolution_clock::now();
			auto pauseDuration = std::chrono::duration_cast<std::chrono::milliseconds>(pauseEnd - pauseStart);
			start += pauseDuration;
			paused = false;
		}
	}

	long long Stats::GetElapsedTime() const
	{
		auto currentTime = paused ? pauseStart : std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - start);
		return duration.count();
	}
}