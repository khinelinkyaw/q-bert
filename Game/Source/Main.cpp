#include <Engine/Core/Minigin.h>
#include <Engine/Core/SceneManager.h>
#include <Engine/Input/InputManager.h>
#include <Engine/Core/ServiceLocator.h>

#include <Components/Scenes/GameOverSceneComponent.h>
#include <Components/Scenes/GameWonSettingsComponent.h>
#include <Components/Scenes/GameplaySettingsComponent.h>
#include <Components/Scenes/HighScoreSettingsComponent.h>
#include <Components/Scenes/StartMenuSettingsComponent.h>
#include <Misc/Constants.h>

#include <SDL3/SDL_main.h>
#include <Components/Scenes/NameInputSettingsComponent.h>

namespace Game
{
    inline static void load()
    {
        std::unordered_map<SoundEffect, std::string> soundFilePaths{
            { SoundEffect::Jump,            "Sounds/jump.mp3" },
            { SoundEffect::Fall,            "Sounds/fall.mp3" },
            { SoundEffect::LevelStart,      "Sounds/level_start.mp3" },
            { SoundEffect::Victory,         "Sounds/victory.mp3" },
            { SoundEffect::SnakeFall,       "Sounds/snake_fall.mp3" },
            { SoundEffect::Ugg,             "Sounds/ugg.mp3" },
            { SoundEffect::Wrongway,        "Sounds/wrongway.mp3" },
        };

        for (const auto& [soundEffect, filePath] : soundFilePaths)
        {
            GameEngine::ServiceLocator::Get().GetSoundSystem().Load(static_cast<int>(soundEffect), filePath);
        }

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
