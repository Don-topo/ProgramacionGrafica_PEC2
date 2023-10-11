#include "Player.h"
#include "GameManager.h"


Player::Player()
{
}

void Player::PreparePlayer()
{
	currentPosition.x = startPositionX;
	currentPosition.y = startPositionY;
	currentState = PlayerState::Idle;
	currentFrame = 0;
	frameCounter = 0;
	maxFrame = 1;
	drawPosition = {0, 0, 32, 32}; // Start for the first frame
}

void Player::UpdatePlayer(PlayerState newState, int posX, int posY)
{
	if (currentState != newState) {
		frameCounter = 0;
		currentFrame = 0;		
		currentState = newState;
	}
	else
	{
		frameCounter++;
	}
	UpdateStateParameters(newState);
	currentPosition.x += posX;
	currentPosition.y += posY;
		
	if (frameCounter / 15 >= 1) {
		frameCounter = 0;
		currentFrame++;
		if (currentFrame >= maxFrame) currentFrame = 0;
	}
	
}

void Player::DrawPlayer()
{
	GameManager & gameManager = GameManager::GetGameManager();
	if (currentState == PlayerState::Dead) {
		DrawTextureRec(gameManager.GetTextureManager().GetTexture(TextureType::PacmanDead), drawPosition, currentPosition, WHITE);
	}
	else {
		DrawTextureRec(gameManager.GetTextureManager().GetTexture(TextureType::Pacman), drawPosition, currentPosition, WHITE);
	}	
}

void Player::ClearPlayer()
{
}

void Player::UpdateStateParameters(PlayerState newState)
{
	switch (newState)
	{
	case PlayerState::Idle:
		maxFrame = 2;
		drawPosition.x = 32 * currentFrame;
		drawPosition.y = 32 * 0;
		break;
	case PlayerState::Left:
		maxFrame = 4;
		drawPosition.x = 32 * currentFrame;
		drawPosition.y = 32 * 1;
		break;
	case PlayerState::Right:
		maxFrame = 2;
		drawPosition.x = 32 * currentFrame;
		drawPosition.y = 32 * 0;
		break;
	case PlayerState::Up:
		maxFrame = 4;
		drawPosition.x = 32 * currentFrame;
		drawPosition.y = 32 * 2;
		break;
	case PlayerState::Down:
		maxFrame = 4;
		drawPosition.x = 32 * currentFrame;
		drawPosition.y = 32 * 3;
		break;
	case PlayerState::Dead:
		maxFrame = 12;
		drawPosition.x = 32 * currentFrame;
		drawPosition.y = 0;
		break;
	default:
		break;
	}
}

void Player::KillPlayer() {
	currentState = PlayerState::Dead;
	frameCounter = 0;
	currentFrame = 0;
}
