#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

enum class PlayerState
{
	Idle = 0,
	Left,
	Right,
	Up,
	Down,
	Dead,
};

class Player
{
public:
	Player();
	void PreparePlayer();
	void UpdatePlayer(PlayerState newState, int posX, int posY);
	void DrawPlayer();
	void ClearPlayer();
	void KillPlayer();
	PlayerState GetCurrentState() { return currentState; };
	Vector2 GetCurrentPosition() { return currentPosition; };
private:
	const int startPositionX = 466;
	const int startPositionY = 594;
	Vector2 currentPosition;	
	PlayerState currentState;
	int currentFrame;
	int frameCounter;
	int maxFrame;
	Rectangle drawPosition;
	void UpdateStateParameters(PlayerState newState);
};

#endif // !PLAYER
