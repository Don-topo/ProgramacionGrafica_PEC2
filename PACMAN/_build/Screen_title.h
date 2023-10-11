#ifndef SCREEN_TITLE_H
#define SCREEN_TITLE_H

#include "raylib.h"


class Screen_title
{

public:
	void InitTitleScreen(void);
	void UpdateTitleScreen(void);
	void DrawTitleScreen(void);
	void UnloadTitleScreen(void);
	int FinishTitleScreen(void);
private:
	const char* titleAutorText = "by Ruben G.";
	const char* titlePlayText = "Press Enter for Playing";
	const char* titleOptionsText = "Press 'O' for Instructions";
	int xPosTitle;
	int yPosTitle;
	int finishScreen = 0;
	Music music;
};

#endif
