#pragma once

#include "core/Defines.hpp"
#include <raylib.h>

class AudioManager
{
public:
	static AudioManager& GetInstance()
	{
		static AudioManager instance;
		return instance;
	}

	void LoadAudio(std::string name, std::string filepath);
	void LoadMusic(std::string name, std::string filepath);

	Sound GetSound(std::string name);
	Music GetMusic(std::string name);

	void Play(std::string name);
	void PlayMusic(std::string name);
	void PauseMusic(std::string name);
	void ResumeMusic(std::string name);

	void SetVolumeSFX(int volume);
	void SetVolumeMusic(int volume);
private:
	AudioManager();
	~AudioManager();

	std::unordered_map<std::string, Sound> sounds;
	std::unordered_map<std::string, Music> musics;
};