#include "AudioManager.hpp"
#include <raylib.h>
#include <core/Utils.hpp>

void AudioManager::LoadAudio(std::string name, std::string filepath)
{
	Sound sound = LoadSound(filepath.c_str());
	sounds.emplace(name, sound);
}

void AudioManager::LoadMusic(std::string name, std::string filepath)
{
	Music music = LoadMusicStream(filepath.c_str());
	PlayMusicStream(music);
	musics.emplace(name, music);
}

Sound AudioManager::GetSound(std::string name)
{
	auto& sound = sounds[name];
	if (sound.stream.buffer == nullptr)
	{
		ERROR("Sound Name Is Probably Wrong");
		return Sound();
	}
	return sound;
}

Music AudioManager::GetMusic(std::string name)
{
	auto& music = musics[name];
	if (music.stream.buffer == nullptr)
	{
		ERROR("Music Name Is Probably Wrong");
		return Music();
	}
	return music;
}

void AudioManager::Play(std::string name)
{
	PlaySound(GetSound(name));
}

void AudioManager::PlayMusic(std::string name)
{
	UpdateMusicStream(GetMusic(name));
}

void AudioManager::PauseMusic(std::string name)
{
	PauseMusicStream(GetMusic(name));
}

void AudioManager::ResumeMusic(std::string name)
{
	ResumeMusicStream(GetMusic(name));
}

AudioManager::~AudioManager()
{
	for (auto& [name, sound] : sounds)
	{
		UnloadSound(sound);
	}

	for (auto& [name, music] : musics)
	{
		UnloadMusicStream(music);
	}

	sounds.clear();
	musics.clear();
}
