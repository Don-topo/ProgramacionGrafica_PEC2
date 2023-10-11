#include "Screen_logo.h"
#include "GameManager.h"

void Screen_logo::InitLogoScreen(void)
{
	xLogoPos = (screenWidth / 2) - (GameManager::GetGameManager().GetTextureManager().GetTexture(TextureType::Logo).width / 2);
	yLogoPos = (screenHeight / 2) - (GameManager::GetGameManager().GetTextureManager().GetTexture(TextureType::Logo).height / 2);
	finishScreen = 0;
}

void Screen_logo::UpdateLogoScreen(void)
{
	transAlpha += 0.01f;
	screenSecondsRemaining -= 1;
	if (screenSecondsRemaining <= 0) {
		finishScreen = 1;
	}
}

void Screen_logo::DrawLogoScreen(void)
{
	DrawTexture(GameManager::GetGameManager().GetTextureManager().GetTexture(TextureType::Logo), xLogoPos, yLogoPos, Fade(WHITE, transAlpha));
}

void Screen_logo::UnloadLogoScreen(void)
{	
	//UnloadTexture(GameManager::GetGameManager().GetTextureManager().GetTexture(TextureType::Logo));
}

int Screen_logo::FinishLogoScreen(void)
{
	return finishScreen;
}
