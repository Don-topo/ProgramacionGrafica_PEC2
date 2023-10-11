#include "GameManager.h"


GameManager* GameManager::GameManager_Ptr = nullptr;

GameManager::GameManager()
{
}

GameManager& GameManager::GetGameManager()
{
    if (GameManager_Ptr == nullptr)
        GameManager_Ptr = new GameManager();
    return *GameManager_Ptr;
}

void GameManager::InitGame()
{
    screenLogo = Screen_logo();
    screenTitle = Screen_title();
    screenOptions = Screen_options();
    screenGameplay = Screen_gameplay();
    screenEnding = Screen_ending();

    player.PreparePlayer();
    enemy.PrepareEnemy();

    textureManager.InitTextures();
    audioManager.InitAudio();

    currentScreen = LOGO;
    screenLogo.InitLogoScreen();
}

void GameManager::UpdateFrame()
{
    audioManager.UpdateMenuMusic();


    if (!onTransition)
    {
        switch (currentScreen)
        {
        case LOGO:
        {
            screenLogo.UpdateLogoScreen();
            if (screenLogo.FinishLogoScreen()) TransitionToScreen(TITLE);

        } break;
        case TITLE:
        {
            screenTitle.UpdateTitleScreen();
            audioManager.PlayMenuMusic(true);
            if (screenTitle.FinishTitleScreen() == 1) TransitionToScreen(OPTIONS);
            else if (screenTitle.FinishTitleScreen() == 2) {              
                TransitionToScreen(GAMEPLAY);
            }

        } break;
        case OPTIONS:
        {
            screenOptions.UpdateOptionsScreen();
            if (screenOptions.FinishOptionsScreen() == 1) TransitionToScreen(TITLE);

        } break;
        case GAMEPLAY:
        {
            screenGameplay.UpdateGameplayScreen(player, enemy);
            audioManager.PlayMenuMusic(false);            
            if (screenGameplay.FinishGameplayScreen() == 1)
            {
                TransitionToScreen(ENDING);
            }

        } break;
        case ENDING:
        {
            screenEnding.UpdateEndingScreen();
            if (screenEnding.FinishEndingScreen() == 1) TransitionToScreen(OPTIONS);
            else if (screenEnding.FinishEndingScreen() == 2)
            {
                TransitionToScreen(GAMEPLAY);
            }


        } break;
        default: break;
        }
    }
    else UpdateTransition();    // Update transition (fade-in, fade-out)
    //----------------------------------------------------------------------------------


}

void GameManager::DrawFrame()
{
    BeginDrawing();

    ClearBackground(BLACK);

    switch (currentScreen)
    {
    case LOGO: screenLogo.DrawLogoScreen(); break;
    case TITLE: screenTitle.DrawTitleScreen(); break;
    case OPTIONS: screenOptions.DrawOptionsScreen(); break;
    case GAMEPLAY: screenGameplay.DrawGameplayScreen(player, enemy); break;
    case ENDING: screenEnding.DrawEndingScreen(); break;
    default: break;
    }

    // Draw full screen rectangle in front of everything
    if (onTransition) DrawTransition();


    EndDrawing();
}

void GameManager::UnloadGame()
{
    switch (currentScreen)
    {
        case LOGO: screenLogo.UnloadLogoScreen(); break;
        case TITLE: screenTitle.UnloadTitleScreen(); break;
        case GAMEPLAY: screenGameplay.UnloadGameplayScreen(); break;
        case ENDING: screenEnding.UnloadEndingScreen(); break;
        default: break;
    }

    //ClearGameVar();

    // Unload global data loaded
    //UnloadFont(font);
    //UnloadMusicStream(music);
    //UnloadSound(fxCoin);

    CloseAudioDevice();     // Close audio context
}

void GameManager::ChangeToScreen(int screen)
{
    // Unload current screen
    switch (currentScreen)
    {
    case LOGO: screenLogo.UnloadLogoScreen(); break;
    case TITLE: screenTitle.UnloadTitleScreen(); break;
    case GAMEPLAY: screenGameplay.UnloadGameplayScreen(); break;
    case ENDING: screenEnding.UnloadEndingScreen(); break;
    default: break;
    }

    // Init next screen
    switch (screen)
    {
    case LOGO: screenLogo.InitLogoScreen(); break;
    case TITLE: screenTitle.InitTitleScreen(); break;
    case GAMEPLAY:
    {
        screenGameplay.InitGameplayScreen();
        audioManager.PlayMenuMusic(false);
        break;
    }
    case ENDING:
    {
        break;
    }
    default: break;
    }

    currentScreen = (GameScreen)screen;
}

// Request transition to next screen
void GameManager::TransitionToScreen(int screen)
{
    onTransition = true;
    transFadeOut = false;
    transFromScreen = currentScreen;
    transToScreen = screen;
    transAlpha = 0.0f;
}

// Update transition effect (fade-in, fade-out)
void GameManager::UpdateTransition(void)
{
    if (!transFadeOut)
    {
        transAlpha += 0.05f;

        // NOTE: Due to float internal representation, condition jumps on 1.0f instead of 1.05f
        // For that reason we compare against 1.01f, to avoid last frame loading stop
        if (transAlpha > 1.01f)
        {
            transAlpha = 1.0f;

            // Unload current screen
            switch (transFromScreen)
            {
            case LOGO: screenLogo.UnloadLogoScreen(); break;
            case TITLE: screenTitle.UnloadTitleScreen(); break;
            case OPTIONS: screenOptions.UnloadOptionsScreen(); break;
            case GAMEPLAY: screenGameplay.UnloadGameplayScreen(); break;
            case ENDING: screenEnding.UnloadEndingScreen(); break;
            default: break;
            }

            // Load next screen
            switch (transToScreen)
            {
            case LOGO: screenLogo.InitLogoScreen(); break;
            case TITLE: screenTitle.InitTitleScreen(); break;
            case GAMEPLAY: screenGameplay.InitGameplayScreen(); break;
            case ENDING: screenEnding.InitEndingScreen(); break;
            case OPTIONS: screenOptions.InitOptionsScreen(); break;
            default: break;
            }

            currentScreen = (GameScreen)transToScreen;

            // Activate fade out effect to next loaded screen
            transFadeOut = true;
        }
    }
    else  // Transition fade out logic
    {
        transAlpha -= 0.02f;

        if (transAlpha < -0.01f)
        {
            transAlpha = 0.0f;
            transFadeOut = false;
            onTransition = false;
            transFromScreen = -1;
            transToScreen = -1;
        }
    }
}

// Draw transition effect (full-screen rectangle)
void GameManager::DrawTransition(void)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, transAlpha));
}

void GameManager::RestartGame() {
    player.PreparePlayer();
    enemy.PrepareEnemy();
    life = 3;
    score = 0;
}