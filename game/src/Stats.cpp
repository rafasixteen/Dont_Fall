#include "Stats.hpp"

namespace Dont_Fall
{
	void Stats::StartTimer()
	{
		if (!paused)
		{
			INFO("Start Timer");
			// Only start the timer if it's not already running
			start = std::chrono::high_resolution_clock::now();
			paused = false;
		}
		else
		{
			std::cerr << "Error: Cannot start the timer when it's already running. Call ResumeTimer() instead." << std::endl;
		}
	}

	void Stats::StopTimer()
	{
		if (!paused)
		{
			INFO("Stop Timer");
			// Only stop the timer if it's not already paused
			stop = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
			time = duration.count();
		}
		else
		{
			std::cerr << "Error: Cannot stop the timer when it's paused. Call ResumeTimer() before stopping." << std::endl;
		}
	}

	void Stats::PauseTimer()
	{
		if (!paused)
		{
			INFO("Paused Timer");
			// Only pause the timer if it's not already paused
			pauseStart = std::chrono::high_resolution_clock::now();
			paused = true;
		}
		else
		{
			std::cerr << "Error: Cannot pause the timer when it's already paused." << std::endl;
		}
	}

	void Stats::ResumeTimer()
	{
		if (paused)
		{
			INFO("Resume Timer");
			// Only resume the timer if it's currently paused
			auto pauseEnd = std::chrono::high_resolution_clock::now();
			auto pauseDuration = std::chrono::duration_cast<std::chrono::milliseconds>(pauseEnd - pauseStart);
			start += pauseDuration;
			paused = false;
		}
		else
		{
			std::cerr << "Error: Cannot resume the timer when it's not paused. Call PauseTimer() before resuming." << std::endl;
		}
	}

	std::string Stats::FormatTime(int milliseconds)
	{
		int seconds = milliseconds / 1000;
		int minutes = seconds / 60;
		seconds %= 60;
		milliseconds %= 1000;

		std::ostringstream formattedTime;
		formattedTime << std::setfill('0') << std::setw(2) << minutes << ":";
		formattedTime << std::setfill('0') << std::setw(2) << seconds << ":";
		formattedTime << std::setfill('0') << std::setw(3) << milliseconds;

		return formattedTime.str();
	}

	int Stats::GetElapsedTime() const
	{
		auto currentTime = paused ? pauseStart : std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - start);
		return duration.count();
	}

	void Stats::SaveStatsToFile(const std::string fileName)
	{
		PlayerStats statsFromFile = LoadStatsFromFile(fileName);
		statsFromFile += playerStats;

		std::ofstream file(fileName);
		if (file.is_open())
		{
			file << statsFromFile.Serialize();
			file.close();
			std::cout << "Stats saved to file: " << fileName << std::endl;
		}
		else
		{
			std::cerr << "Unable to open file: " << fileName << std::endl;
		}
	}

	PlayerStats Stats::LoadStatsFromFile(const std::string filename)
	{
		std::ifstream file(filename);
		PlayerStats loadedStats{};

		if (file.is_open())
		{
			std::string line;
			if (std::getline(file, line))
			{
				std::istringstream ss(line);
				ss >> loadedStats.time >> loadedStats.gamesPlayed >> loadedStats.died >> loadedStats.ammoCollected;
				file.close();
			}
		}

		return loadedStats;
	}
}