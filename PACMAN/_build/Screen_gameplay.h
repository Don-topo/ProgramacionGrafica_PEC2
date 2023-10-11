#ifndef SCREEN_GAMEPLAY_H
#define SCREEN_GAMEPLAY_H

#include "raylib.h"
#include "Player.h"
#include "Enemy.h"
#include "TextureManager.h"

class Screen_gameplay
{
public:
	Screen_gameplay(){};
	void InitGameplayScreen();
	void UpdateGameplayScreen(Player& player, Enemy& enemy);
	void DrawGameplayScreen(Player& player, Enemy& enemy);
	void UnloadGameplayScreen();
	int FinishGameplayScreen();

private:
	int finishScreen = 0;
	Tilemap map = {0};
	bool CanMove(Player& player, int newPositionX, int newPositionY);
	void CheckObjects(Player& player, Enemy& enemy);
	bool PlayerWin();
	bool PlayerLoses();
	void CheckCharactersContact(Player& player, Enemy& enemy);
	void WaitDeadAnimation(Player& player, Enemy& enemy);
	int deadTimeCounter;
	static const int dotScore = 10;
	static const int pillScore = 50;
	static const int ghostScore = 200;
	int movePositionY = 0;
	int movePositionX = 0;
};


#endif // !SCREEN_GAMEPLAY_H



