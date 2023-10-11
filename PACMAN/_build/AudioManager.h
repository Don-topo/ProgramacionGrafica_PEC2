#pragma once

#include "raylib.h"

enum class SoundType {
	Waka,
	Pill,
	Ghost,
	Dead,
	Win,
};

class AudioManager
{
public:
	AudioManager();
	void InitAudio();
	void UnloadAudio();
	void PlayMenuMusic(bool activate);
	void UpdateMenuMusic();
	void PlaySoundEffect(SoundType sound);
	void StopSoundEffect(SoundType sound);

private:
	Music menuMusic;

	Sound wakaSound;
	Sound pillSound;
	Sound ghostSound;
	Sound pacmanDeadSound;
	Sound victorySound;
};

