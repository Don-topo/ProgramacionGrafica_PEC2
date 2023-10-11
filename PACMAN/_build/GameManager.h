#pragma once
#include "Screen_logo.h"
#include "Screen_title.h"
#include "Screen_options.h"
#include "Screen_gameplay.h"
#include "Screen_ending.h"
#include "TextureManager.h"
#include "AudioManager.h"
#include "Enemy.h"

typedef enum GameScreen { LOGO = 0, TITLE, OPTIONS, GAMEPLAY, ENDING } GameScreen;

class GameManager
{
public:
	GameManager();
	static GameManager& GetGameManager();
	TextureManager& GetTextureManager() { return textureManager; };
	AudioManager& GetAudioManager() { return audioManager; };
	void InitGame();
	void UpdateFrame();
	void DrawFrame();
	void UnloadGame();
	int GetScore() { return score; };
	int GetLifes() { return life; };
	void LoseLife() { life -= 1; };
	void AddScore(int amount) { score += amount; };
	void RestartGame();

private:
	
	static GameManager* GameManager_Ptr;
	GameScreen currentScreen = GameScreen::LOGO;

	void ChangeToScreen(int screen);
	void TransitionToScreen(int screen);
	void UpdateTransition();
	void DrawTransition();

	float transAlpha = 0.0f;
	bool onTransition = false;
	bool transFadeOut = false;
	int transFromScreen = -1;
	int transToScreen = -1;

	// Screens
	Screen_logo screenLogo;
	Screen_title screenTitle;
	Screen_options screenOptions;
	Screen_gameplay screenGameplay;
	Screen_ending screenEnding;

	// Managers
	TextureManager textureManager = TextureManager();;
	AudioManager audioManager = AudioManager();

	Player player = Player();
	Enemy enemy = Enemy();
	int score = 0;
	int life = 3;
};

