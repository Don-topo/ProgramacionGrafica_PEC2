#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"

enum class GhostState {
	Chase,
	Frightened,
	eaten
};

enum class Directions {
	Up,
	Down,
	Left,
	Right
};

typedef struct Movement {
	Vector2 position;
	int distance;
	bool collision;
	Directions direction;
} Movement;

class Enemy
{
public:
	Enemy();
	void PrepareEnemy();
	void UpdateEnemy(Vector2 playerPosition);
	void DrawEnemy();
	GhostState GetCurrentState() { return currentState; };
	Vector2 GetCurrentPosition() { return currentPosition; };
	void GetFrightened();
	void GetEaten();
	void GetChasing();
private:
	GhostState currentState;
	Vector2 startPosition;
	Vector2 currentPosition;
	Vector2 frightenedPostion;
	Rectangle drawPosition;
	Vector2 nextTile;
	Vector2 moveDirection;
	Movement directions[3];
	static const int maxTimeFrightened = 10;
	int frightenedCounter;
	void Move(Vector2 targetPosition);
	void CheckDirections();
	Vector2 GetLowestPath(Vector2 targetPosition);
	void SetDirection(Movement direction);
	void RestartMovementData();
};

#endif // !ENEMY_H;