#ifndef SCREEN_OPTIONS_H
#define SCREEN_OPTIONS_H


#include "raylib.h"


class Screen_options
{

public:
	void InitOptionsScreen(void);
	void UpdateOptionsScreen(void);
	void DrawOptionsScreen(void);
	void UnloadOptionsScreen(void);
	int FinishOptionsScreen(void);
private:
	int finishScreen;
	const char* optionsMovementText = "To move PACMAN use direction keys or A,D,W,S.";
	const char* optionsDescriptionText = "PACMAN has 3 lifes, every dot eaten increases 10 points";
	const char* optionsDescriptionText2 = "the big dots adds 50 points to the score.";
	const char* optionsWinText = "To win PACMAN has to eat all the dots";
	const char* optionsLoseText = "You loose if the ghost SHADOW kills you 3 times.";
	const char* optionsReturnText = "Press 'O' to return to Title.";
};

#endif // !SCREEN_OPTIONS_H