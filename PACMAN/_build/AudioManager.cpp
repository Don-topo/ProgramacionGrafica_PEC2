#include "AudioManager.h"

AudioManager::AudioManager() {};

void AudioManager::InitAudio()
{
	InitAudioDevice();
	menuMusic = LoadMusicStream("resources/Audio/Music/IntroTheme.mp3");
	wakaSound = LoadSound("resources/Audio/Sounds/WakaWaka.mp3");
	pillSound = LoadSound("resources/Audio/Sounds/EatingPowerPill.mp3");
	ghostSound = LoadSound("resources/Audio/Sounds/EatingGhost.mp3");
	pacmanDeadSound = LoadSound("resources/Audio/Sounds/Death.mp3");
	victorySound = LoadSound("resources/Audio/Sounds/Victory.mp3");
	SetMusicVolume(menuMusic, 1.0f);
}

void AudioManager::UnloadAudio()
{
	UnloadSound(wakaSound);
	UnloadSound(pillSound);
	UnloadSound(ghostSound);
	UnloadSound(pacmanDeadSound);
	UnloadSound(victorySound);
	CloseAudioDevice();
}

void AudioManager::PlayMenuMusic(bool activate)
{
	if (activate) {
		PlayMusicStream(menuMusic);
	}
	else
	{
		StopMusicStream(menuMusic);
	}
}

void AudioManager::UpdateMenuMusic()
{
	UpdateMusicStream(menuMusic);
}

void AudioManager::PlaySoundEffect(SoundType sound)
{
	switch (sound)
	{
	case SoundType::Waka:
		PlaySound(wakaSound);
		break;
	case SoundType::Pill:
		PlaySound(pillSound);
		break;
	case SoundType::Ghost:
		PlaySound(ghostSound);
		break;
	case SoundType::Dead:
		PlaySound(pacmanDeadSound);
		break;
	case SoundType::Win:
		PlaySound(victorySound);
		break;
	default:
		break;
	}
}

void AudioManager::StopSoundEffect(SoundType sound) {
	switch (sound)
	{
	case SoundType::Waka:
		StopSound(wakaSound);
		break;
	case SoundType::Pill:
		StopSound(pillSound);
		break;
	case SoundType::Ghost:
		StopSound(ghostSound);
		break;
	case SoundType::Dead:
		StopSound(pacmanDeadSound);
		break;
	case SoundType::Win:
		StopSound(victorySound);
		break;
	default:
		break;
	}
}
