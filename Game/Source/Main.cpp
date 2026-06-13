#include <Engine/Core/Minigin.h>
#include <Engine/Core/SceneManager.h>
#include <Engine/Input/InputManager.h>

#include <Components/Scenes/GameOverSceneComponent.h>
#include <Components/Scenes/GameWonSettingsComponent.h>
#include <Components/Scenes/GameplaySettingsComponent.h>
#include <Components/Scenes/HighScoreSettingsComponent.h>
#include <Components/Scenes/StartMenuSettingsComponent.h>
#include <Misc/Constants.h>
#include <UserInterface/UIEngine.h>

#include <SDL3/SDL_main.h>
#include <Components/Scenes/NameInputSettingsComponent.h>

namespace Game
{
    inline static void load()
    {
        GameEngine::InputManager::Get().ImportInputMappingJSON("JSON/InputMappings.json");

        auto& startMenu = GameEngine::SceneManager::Get().CreateScene("StartMenu");
        GameEngine::SceneManager::Get().SetActiveScene(&startMenu);
        GameEngine::SceneManager::Get().CheckForSceneChange();
        auto& startMenuSettingsObj{ startMenu.CreateGameObject("StartMenuSettings") };
        startMenuSettingsObj.AddComponent<StartMenuSettingsComponent>();

        auto& gameplayScene = GameEngine::SceneManager::Get().CreateScene("Gameplay");
        GameEngine::SceneManager::Get().SetActiveScene(&gameplayScene);
        GameEngine::SceneManager::Get().CheckForSceneChange();
        auto& gameplaySettingsObj{ gameplayScene.CreateGameObject("GameplaySettings") };
        gameplaySettingsObj.AddComponent<GameplaySettingsComponent>()->Init("JSON/Levels.json");

        auto& gameOverScene{ GameEngine::SceneManager::Get().CreateScene("GameOver") };
        GameEngine::SceneManager::Get().SetActiveScene(&gameOverScene);
        GameEngine::SceneManager::Get().CheckForSceneChange();
        auto& gameOverSettingsObj{ gameOverScene.CreateGameObject("GameOverSettings") };
        gameOverSettingsObj.AddComponent<GameOverSceneComponent>();

        auto& gameWonScene{ GameEngine::SceneManager::Get().CreateScene("GameWon") };
        GameEngine::SceneManager::Get().SetActiveScene(&gameWonScene);
        GameEngine::SceneManager::Get().CheckForSceneChange();
        auto& gameWonSettingObj{ gameWonScene.CreateGameObject("GameWonSettings") };
        gameWonSettingObj.AddComponent<GameWonSettingsComponent>();

        auto& nameInputScene = GameEngine::SceneManager::Get().CreateScene("NameInput");
        GameEngine::SceneManager::Get().SetActiveScene(&nameInputScene);
        GameEngine::SceneManager::Get().CheckForSceneChange();
        auto& nameInputSettingsObj{ nameInputScene.CreateGameObject("NameInputSettings") };
        nameInputSettingsObj.AddComponent<NameInputSettingsComponent>();

        auto& highScoreScene{ GameEngine::SceneManager::Get().CreateScene("HighScore") };
        GameEngine::SceneManager::Get().SetActiveScene(&highScoreScene);
        GameEngine::SceneManager::Get().CheckForSceneChange();
        auto& highScoreSettingObj{ highScoreScene.CreateGameObject("HighScoreSettings") };
        highScoreSettingObj.AddComponent<HighScoreSettingsComponent>();

        GameEngine::SceneManager::Get().SetActiveScene(&startMenu);

        GameEngine::Minigin::SetGameScreenSize(Screen::GAME_WIDTH, Screen::GAME_HEIGHT);
        GameEngine::Minigin::MaximizeWindow();
    }
}

int main(int, char* [])
{
    GameEngine::RunGame(Game::load);
    return 0;
}
