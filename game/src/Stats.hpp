#pragma once

#include "core/Defines.hpp"

struct PlayerStats
{
	int time; // In milliseconds
	int gamesPlayed;
	int died;
	int ammoCollected;

	std::string Serialize() const
	{
		std::ostringstream ss;
		ss << time << " " << gamesPlayed << " " << died << " " << ammoCollected << "\n";

		return ss.str();
	}

	void Deserialize(const std::string data)
	{
		std::istringstream ss(data);
		ss >> time >> gamesPlayed >> died >> ammoCollected;
	}

	PlayerStats& operator+=(PlayerStats& other)
	{
		if (other.time > this->time) this->time = other.time; // Only Save The Time If It's Bigger Than The StatFromFile (other)
		this->gamesPlayed += other.gamesPlayed;
		this->died += other.died;
		this->ammoCollected += other.ammoCollected;

		other = {};

		return *this;
	}
};

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

	static std::string FormatTime(int milliseconds);

	int GetElapsedTime() const;
	int GetTime() const { return time; }
	PlayerStats& GetPlayerStats() { return playerStats; }

	void SaveStatsToFile(const std::string fileName);
	PlayerStats LoadStatsFromFile(const std::string fileName);
private:
	Stats() {}
	PlayerStats playerStats{};

	std::chrono::time_point<std::chrono::high_resolution_clock> start;
	std::chrono::time_point<std::chrono::high_resolution_clock> stop;
	int time = 0; // Time Is Equal To The Total In Miliseconds 

	std::chrono::time_point<std::chrono::high_resolution_clock> pauseStart;
	bool paused = false;
};

