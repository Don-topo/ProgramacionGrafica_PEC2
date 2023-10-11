#include "raylib.h"
#include "GlobalGameDefines.h"
#include "GameManager.h"


int main() {

	double currentGameTime = 0.0f;
	double initialGameTime = 0.0f;


	InitWindow(screenWidth, screenHeight, screenTitle);
	SetTargetFPS(60);
	GameManager& gameManager = GameManager::GetGameManager();
	gameManager.InitGame();

	while (!WindowShouldClose())
	{
		currentGameTime = GetTime();
		int seconds = (int)currentGameTime % 60;

		// Update
		gameManager.UpdateFrame();
		// Draw
		gameManager.GetGameManager().DrawFrame();
	}

	gameManager.UnloadGame();
	CloseWindow();

	return 0;
}