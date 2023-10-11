#include "Screen_title.h"
#include "GameManager.h"

void Screen_title::InitTitleScreen(void) {	
	xPosTitle = (GetScreenWidth() / 2) - (GameManager::GetGameManager().GetTextureManager().GetTexture(TextureType::Title).width / 2);
	yPosTitle = (GetScreenHeight() / 4) - (GameManager::GetGameManager().GetTextureManager().GetTexture(TextureType::Title).height / 2);
	finishScreen = 0;
}

void Screen_title::UpdateTitleScreen(void) {
	if (IsKeyDown(KEY_ENTER)) finishScreen = 2;
	if (IsKeyDown(KEY_O)) finishScreen = 1;
}

void Screen_title::DrawTitleScreen(void) {
	DrawTexture(GameManager::GetGameManager().GetTextureManager().GetTexture(TextureType::Title), xPosTitle, yPosTitle, WHITE);
	DrawText(titleAutorText, GetScreenWidth() / 2 - 60, (yPosTitle + GameManager::GetGameManager().GetTextureManager().GetTexture(TextureType::Title).height), 24, WHITE);
	DrawText(titlePlayText, (GetScreenWidth() / 2 - 235), (yPosTitle + GameManager::GetGameManager().GetTextureManager().GetTexture(TextureType::Title).height + 180), 36, WHITE);
	DrawText(titleOptionsText, (GetScreenWidth() / 2 - 250), (yPosTitle + GameManager::GetGameManager().GetTextureManager().GetTexture(TextureType::Title).height + 220), 36, WHITE);
}

void Screen_title::UnloadTitleScreen(void) {
	//UnloadTexture(GameManager::GetGameManager().GetTextureManager().GetTexture(TextureType::Title));
	finishScreen = 0;
}

int Screen_title::FinishTitleScreen(void) {
	return finishScreen;
}
