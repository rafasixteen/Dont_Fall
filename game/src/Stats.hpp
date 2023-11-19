#pragma once

#include "core/Defines.hpp"

namespace Dont_Fall
{
	class Stats
	{
	public:
		static Stats& GetInstance()
		{
			static Stats instance;
			return instance;
		}

		void StartTimer();
		void StopTimer();

		void PauseTimer();
		void ResumeTimer();

		long long GetElapsedTime() const;
		long long GetTime() const { return time; }
	private:
		Stats() {}

		std::chrono::time_point<std::chrono::high_resolution_clock> start;
		std::chrono::time_point<std::chrono::high_resolution_clock> stop;
		long long time = 0; // Time Is Equal To The Total In Miliseconds 

		std::chrono::time_point<std::chrono::high_resolution_clock> pauseStart;
		bool paused = false;
	};
}
