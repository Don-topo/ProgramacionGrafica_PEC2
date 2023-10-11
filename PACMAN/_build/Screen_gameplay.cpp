#include "Screen_gameplay.h"
#include "GameManager.h"
#include <string>

void Screen_gameplay::InitGameplayScreen()
{
    finishScreen = 0;
    GameManager::GetGameManager().RestartGame();
    GameManager::GetGameManager().GetTextureManager().ReloadTilemap();
    map = GameManager::GetGameManager().GetTextureManager().GetTileMap();
    deadTimeCounter = 0;
    movePositionY = 0;
    movePositionX = 0;
}

void Screen_gameplay::UpdateGameplayScreen(Player& player, Enemy& enemy)
{
   PlayerState newState = player.GetCurrentState();
   int moveNewPositionY = 0;
   int moveNewPositionX = 0;

    if ((IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) && player.GetCurrentState() != PlayerState::Dead) {       
        newState = PlayerState::Left;
        moveNewPositionX = -2;
    }

    if ((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) && player.GetCurrentState() != PlayerState::Dead) {
        newState = PlayerState::Right;
        moveNewPositionX = 2;
    }

    if ((IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) && player.GetCurrentState() != PlayerState::Dead) {
        newState = PlayerState::Up;
        moveNewPositionY = -2;
    }

    if ((IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) && player.GetCurrentState() != PlayerState::Dead) {
        newState = PlayerState::Down;
        moveNewPositionY = 2;
    }

    // New Movement
    if (CanMove(player, moveNewPositionX, moveNewPositionY) && (moveNewPositionX != 0 || moveNewPositionY != 0) || player.GetCurrentState() == PlayerState::Dead) {
        movePositionX = moveNewPositionX;
        movePositionY = moveNewPositionY;        
    }
    else {
        // AutoMove
        if (!CanMove(player, movePositionX, movePositionY) || player.GetCurrentState() == PlayerState::Dead) {
            movePositionX = 0;
            movePositionY = 0;
        }
        newState = player.GetCurrentState();
    }
    player.UpdatePlayer(newState, movePositionX, movePositionY);
    if (player.GetCurrentState() != PlayerState::Dead) {
        enemy.UpdateEnemy(player.GetCurrentPosition());
    }
    else {
        WaitDeadAnimation(player, enemy);
    }    
    CheckCharactersContact(player, enemy);
    CheckObjects(player, enemy);
    if (PlayerWin()) finishScreen = 1;
    if (PlayerLoses()) finishScreen = 1;
}

void Screen_gameplay::DrawGameplayScreen(Player& player, Enemy& enemy)
{
    GameManager& gameManager = GameManager::GetGameManager();    
    gameManager.GetTextureManager().DrawTileMap();
    player.DrawPlayer();
    enemy.DrawEnemy();
    DrawText("SCORE:", 25, 10, 32, WHITE);
    DrawText(std::to_string(GameManager::GetGameManager().GetScore()).c_str(), 225, 10, 32, WHITE);
    for (int i = 0; i < gameManager.GetLifes();i++) {
        DrawTexture(gameManager.GetTextureManager().GetTexture(TextureType::PacmanLifes), 800 + (i * 32), 10, WHITE);
    }
}

void Screen_gameplay::UnloadGameplayScreen()
{
}

int Screen_gameplay::FinishGameplayScreen()
{
    return finishScreen;
}

bool Screen_gameplay::CanMove(Player& player, int newPositionX, int newPositionY)
{
    Rectangle playerCollider = { player.GetCurrentPosition().x + newPositionX + 16 , player.GetCurrentPosition().y + newPositionY + 16, 28, 28 };
    for (int y = 0; y < map.tileCountY; y++){
        for (int x = 0; x < map.tileCountX; x++){
            Rectangle tileCollider = { 50.f + (x * map.tileSize) + 16 , 50.f + (y * map.tileSize) + 16, map.tileSize, map.tileSize};            
            if (map.tiles[x + (y * map.tileCountX)].collider == 1 && CheckCollisionRecs(playerCollider, tileCollider)) {
                return false;
            }
        }
    }
    return true;
}

void Screen_gameplay::CheckObjects(Player& player, Enemy& enemy)
{
    Rectangle playerCollider = { player.GetCurrentPosition().x + 16, player.GetCurrentPosition().y + 16, 28, 28};
    for (int y = 0; y < map.tileCountY; y++) {
        for (int x = 0; x < map.tileCountX; x++) {
            Rectangle tileCollider = { 50.f + (x * map.tileSize) + 16 , 50.f + (y * map.tileSize) + 16, 8, 8 };
            if (map.tiles[x + (y * map.tileCountX)].value == 29 && CheckCollisionRecs(playerCollider, tileCollider)) {
                GameManager::GetGameManager().AddScore(dotScore);
                map.tiles[x + (y * map.tileCountX)].value = 11;
                GameManager::GetGameManager().GetAudioManager().PlaySoundEffect(SoundType::Waka);
                return;
            }
            else if (map.tiles[x + (y * map.tileCountX)].value == 27 && CheckCollisionRecs(playerCollider, tileCollider)) {
                GameManager::GetGameManager().AddScore(pillScore);
                map.tiles[x + (y * map.tileCountX)].value = 11;
                GameManager::GetGameManager().GetAudioManager().PlaySoundEffect(SoundType::Pill);
                enemy.GetFrightened();
                return;
            }
        }
    }
}

bool Screen_gameplay::PlayerWin()
{
    for (int y = 0; y < map.tileCountY; y++) {
        for (int x = 0; x < map.tileCountX; x++) {
            if (map.tiles[x + (y * map.tileCountX)].value == 29 || map.tiles[x + (y * map.tileCountX)].value == 27) {
                return false;
            }
        }
    }
    return true;
}

bool Screen_gameplay::PlayerLoses()
{
    return(GameManager::GetGameManager().GetLifes() <= 0);
}

void Screen_gameplay::CheckCharactersContact(Player& player, Enemy& enemy)
{
    Rectangle playerRectangle = { player.GetCurrentPosition().x, player.GetCurrentPosition().y, 32, 32 };
    Rectangle enemyRectangle = { enemy.GetCurrentPosition().x, enemy.GetCurrentPosition().y, 32, 32 };
    if (CheckCollisionRecs(playerRectangle, enemyRectangle) && player.GetCurrentState() != PlayerState::Dead) {
        switch (enemy.GetCurrentState())
        {
        case GhostState::Frightened:
            enemy.GetEaten();
            GameManager::GetGameManager().AddScore(ghostScore);
            GameManager::GetGameManager().GetAudioManager().PlaySoundEffect(SoundType::Ghost);
            break;
        case GhostState::Chase:            
            GameManager::GetGameManager().LoseLife();
            // Play deadEffect            
            GameManager::GetGameManager().GetAudioManager().PlaySoundEffect(SoundType::Dead);
            player.KillPlayer();
            break;
        default:
            break;
        }
    }
}

void Screen_gameplay::WaitDeadAnimation(Player& player, Enemy& enemy) {
    deadTimeCounter++;
    if (deadTimeCounter / 60 > 2) {
        player.PreparePlayer();
        enemy.PrepareEnemy();
        deadTimeCounter = 0;
    }
}
