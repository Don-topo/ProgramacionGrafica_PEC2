#include "Enemy.h"
#include "GameManager.h"

Enemy::Enemy()
{
	startPosition = { 50 + 13 * 32, 50 + 11 * 32};
	frightenedPostion = { 50 + 32, 0 };
}

void Enemy::PrepareEnemy()
{
	currentPosition = startPosition;
	currentState = GhostState::Chase;
	drawPosition = {0, 0, 32, 32};
	frightenedCounter = 0;
	RestartMovementData();
}

void Enemy::UpdateEnemy(Vector2 playerPosition)
{
	switch (currentState)
	{
		case GhostState::Frightened:
			frightenedCounter++;
			if (frightenedCounter / 60 >= maxTimeFrightened) {
				GetChasing();				
			}
			Move(frightenedPostion);
		break;
		case GhostState::eaten:
			if (currentPosition.x == startPosition.x && currentPosition.y == startPosition.y) {
				RestartMovementData();
				GameManager::GetGameManager().GetAudioManager().StopSoundEffect(SoundType::Pill);
				GetChasing();
			}
			Move(startPosition);
			break;
		case GhostState::Chase:
			Move(playerPosition);
			break;
	default:
		break;
	}

}

void Enemy::DrawEnemy()
{
	DrawTextureRec(GameManager::GetGameManager().GetTextureManager().GetTexture(TextureType::Ghost), drawPosition, currentPosition, WHITE);
}

void Enemy::GetFrightened()
{
	if (currentState != GhostState::eaten) {
		currentState = GhostState::Frightened;
		frightenedCounter = 0;
		drawPosition.x = 32 * 8 - 2;
		drawPosition.y = 0;
	}	
}

void Enemy::GetEaten()
{
	currentState = GhostState::eaten;
	drawPosition.x = 32 * 8;
	drawPosition.y = 32 * 1;
}

void Enemy::GetChasing()
{
	drawPosition.x = 0;
	drawPosition.y = 0;
	currentState = GhostState::Chase;
}

void Enemy::Move(Vector2 targetPosition) {

	if (nextTile.x == 0 && nextTile.y == 0) {
		directions[0] = { { currentPosition.x, currentPosition.y - 32 }, 0, false, Directions::Up }; // Up
		moveDirection.x = 0;
		moveDirection.y = -2;
		CheckDirections();
		nextTile = GetLowestPath(targetPosition);
	}
	// Check if we reached the center of the tile
	else if (currentPosition.x == nextTile.x && currentPosition.y == nextTile.y) {
		// Calculate next Tile
		if (moveDirection.x > 0) {
			// Last move was Right
			directions[0] = { { currentPosition.x + 32, currentPosition.y }, 0, false, Directions::Right }; // Right			
			directions[1] = { { currentPosition.x, currentPosition.y - 32 }, 0, false, Directions::Up }; // Up
			directions[2] = { { currentPosition.x, currentPosition.y + 32 }, 0, false, Directions::Down };  // Down
		}
		if (moveDirection.x < 0) {
			// Last move was Left
			directions[0] = { { currentPosition.x - 32, currentPosition.y }, 0, false, Directions::Left }; // Left			
			directions[1] = { { currentPosition.x, currentPosition.y - 32 }, 0, false, Directions::Up }; // Up
			directions[2] = { { currentPosition.x, currentPosition.y + 32 }, 0, false, Directions::Down };  // Down
		}
		if (moveDirection.y > 0) {
			// Last move vas Down
			directions[0] = { { currentPosition.x + 32, currentPosition.y }, 0, false, Directions::Right }; // Right
			directions[1] = { { currentPosition.x, currentPosition.y + 32 }, 0, false, Directions::Down };  // Down
			directions[2] = { { currentPosition.x - 32, currentPosition.y }, 0, false, Directions::Left };  // Left
		}
		if (moveDirection.y < 0) {
			// Last move was Up
			directions[0] = { { currentPosition.x + 32, currentPosition.y }, 0, false, Directions::Right }; // Right
			directions[1] = { { currentPosition.x - 32, currentPosition.y }, 0, false, Directions::Left }; // Left
			directions[2] = { { currentPosition.x, currentPosition.y - 32 }, 0, false, Directions::Up }; // Up
		}
		CheckDirections();
		nextTile = GetLowestPath(targetPosition);
	}
	else {
		// Move
		currentPosition.x += moveDirection.x;
		currentPosition.y += moveDirection.y;
	}
}

void Enemy::CheckDirections()
{	
	Tilemap map = GameManager::GetGameManager().GetTextureManager().GetTileMap();
	for (int y = 0; y < map.tileCountY; y++) {
		for (int x = 0; x < map.tileCountX; x++) {
			Rectangle tileCollider = { 50.f + (x * map.tileSize) + 16 , 50.f + (y * map.tileSize) + 16, 8, 8 };
			for (int i = 0; i < 3; i++) {
				Rectangle enemyCollider = { directions[i].position.x + 16, directions[i].position.y + 16, 32, 32};
				if (map.tiles[x + (y * map.tileCountX)].collider == 1 && CheckCollisionRecs(enemyCollider, tileCollider)) {
					directions[i].collision = true;
				}
			}			
		}
	}
}

Vector2 Enemy::GetLowestPath(Vector2 targetPosition) {
	Vector2 minV = {0};
	int distance = 100000000;

	for (int i = 0; i < 3; i++) {
		if (!directions[i].collision) {
			directions[i].distance = pow((abs(directions[i].position.x - targetPosition.x) / 32), 2) + pow((abs(directions[i].position.y - targetPosition.y) / 32), 2);
			if (distance > directions[i].distance) {
				distance = directions[i].distance;
				SetDirection(directions[i]);
				minV = { directions[i].position.x, directions[i].position.y };
			}
		}
	}
	return minV;
}

void Enemy::SetDirection(Movement direction) {
	switch (direction.direction)
	{
	case Directions::Up:
		moveDirection = { 0, -2 };
		break;
	case Directions::Down:
		moveDirection = { 0, 2 };
		break;
	case Directions::Left:
		moveDirection = { -2, 0 };
		break;
	case Directions::Right:
		moveDirection = { 2, 0 };
		break;
	default:
		break;
	}
}

void Enemy::RestartMovementData() {
	directions[0] = {};
	directions[1] = {};
	directions[2] = {};
	nextTile = { 0, 0 };
	moveDirection = { 0, 0 };
}
