#ifndef SCREEN_ENDING_H
#define SCREEN_ENDING_H

#include "raylib.h"

class Screen_ending
{
public:
	void InitEndingScreen(void);
	void UpdateEndingScreen(void);
	void DrawEndingScreen(void);
	void UnloadEndingScreen(void);
	int FinishEndingScreen(void);
private:
	const char* loseTitleText = "you LOOSE!! :(";
	const char* winTitleText = "you WIN!! :)";
	const char* loseMainTitleText = "Press Enter for Playing Again";
	const char* loseOptionsText = "Press 'O' for Options";
	int finishScreen;
	Music music;
};

#endif // !SCREEN_ENDING_H