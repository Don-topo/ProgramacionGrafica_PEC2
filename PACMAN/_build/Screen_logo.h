#ifndef SCREEN_LOGO_H
#define SCREEN_LOGO_H

#include "raylib.h"
#include "GlobalGameDefines.h"


class Screen_logo {
public:
	Screen_logo() {};
	void InitLogoScreen(void);
	void UpdateLogoScreen(void);
	void DrawLogoScreen(void);
	void UnloadLogoScreen(void);
	int FinishLogoScreen(void);
private:
	int screenSecondsRemaining = 200;
	int finishScreen = 0;
	float transAlpha = 0.0f;
	int xLogoPos = 0;
	int yLogoPos = 0;
};

#endif // !SCREEN_LOGO_H


