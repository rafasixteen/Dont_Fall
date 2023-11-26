#include "Stats.hpp"
#include "Game.hpp"

void Stats::StartTimer()
{
	start = std::chrono::high_resolution_clock::now();
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

void Stats::SaveStatsToFile()
{
	const std::string filename = "stats.ini";

	PlayerStats statsFromFile = LoadStatsFromFile();
	statsFromFile += playerStats;

	std::ofstream file(filename);
	if (file.is_open())
	{
		file << statsFromFile.Serialize();
		file.close();
		INFO("Stats saved to file: " << filename);
	}
	else
	{
		WARNING("Unable to open file: " << filename);
	}
}

PlayerStats Stats::LoadStatsFromFile()
{
	const std::string filename = "stats.ini";

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
	else
	{
		WARNING("Unable to open file: " << filename);
		return PlayerStats();
	}

	return loadedStats;
}
