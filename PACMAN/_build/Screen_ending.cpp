#include "Screen_ending.h"
#include "GameManager.h"

void Screen_ending::InitEndingScreen(void) {
	finishScreen = 0;
	music = LoadMusicStream("resources/Lose.wav");
	music.looping = false;
	SetMusicVolume(music, 1.f);
	PlayMusicStream(music);
}

void Screen_ending::UpdateEndingScreen(void) {
	if (IsKeyDown(KEY_O)) finishScreen = 1;
	if (IsKeyDown(KEY_ENTER)) finishScreen = 2;
	UpdateMusicStream(music);
}

void Screen_ending::DrawEndingScreen(void) {
	if (GameManager::GetGameManager().GetLifes() > 0) {
		DrawText(winTitleText, GetScreenWidth() / 2 - 75, GetScreenHeight() / 2 - 50, 24, WHITE);
		GameManager::GetGameManager().GetAudioManager().PlaySoundEffect(SoundType::Win);
	}
	else {
		DrawText(loseTitleText, GetScreenWidth() / 2 - 75, GetScreenHeight() / 2 - 50, 24, WHITE);
	}	
	DrawText(loseMainTitleText, GetScreenWidth() / 2 - 160, GetScreenHeight() / 2 + 150, 24, WHITE);
	DrawText(loseOptionsText, GetScreenWidth() / 2 - 125, GetScreenHeight() / 2 + 200, 24, WHITE);
}

void Screen_ending::UnloadEndingScreen(void) {
	UnloadMusicStream(music);
	finishScreen = 0;
}

int Screen_ending::FinishEndingScreen(void) {
	return finishScreen;
}