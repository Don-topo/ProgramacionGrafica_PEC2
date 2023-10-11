#include "Screen_options.h"

void Screen_options::InitOptionsScreen(void) {
	finishScreen = 0;
}

void Screen_options::UpdateOptionsScreen(void) {
	if (IsKeyDown(KEY_O)) finishScreen = 1;
}

void Screen_options::DrawOptionsScreen(void) {
	DrawText(optionsMovementText, GetScreenWidth() / 4 - sizeof(optionsMovementText) * 10, 80, 24, WHITE);
	DrawText(optionsDescriptionText, GetScreenWidth() / 2 - 350, 120, 24, WHITE);
	DrawText(optionsDescriptionText2, GetScreenWidth() / 2 - 250, 160, 24, WHITE);
	DrawText(optionsWinText, GetScreenWidth() / 4 - 50, 200, 24, WHITE);
	DrawText(optionsLoseText, GetScreenWidth() / 2 - 275, 240, 24, WHITE);
	DrawText(optionsReturnText, GetScreenWidth() / 2 - 175, 360, 24, WHITE);
}

void Screen_options::UnloadOptionsScreen(void) {
	finishScreen = 0;
}

int Screen_options::FinishOptionsScreen(void) {
	return finishScreen;
}