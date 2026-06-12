#include <Engine/Core/Minigin.h>
#include <Engine/Core/SceneManager.h>
#include <Engine/Input/InputManager.h>
#include <Engine/Input/InputMapping.h>
#include <Engine/Misc/Enums.h>

#include <Components/Scenes/GameplaySettingsComponent.h>
#include <Components/Scenes/StartMenuSettingsComponent.h>
#include <Components/Scenes/GameOverSceneComponent.h>
#include <Components/Scenes/GameWonSettingsComponent.h>
#include <Components/Scenes/HighScoreSettingsComponent.h>
#include <Misc/Constants.h>

#include <memory>
#include <utility>

#include <SDL3/SDL_main.h>

namespace Game
{
    inline static void load()
    {
        std::unique_ptr<GameEngine::InputMapping> generalInput{ std::make_unique<GameEngine::InputMapping>() };
        generalInput->SetActionMapping("SelectorUp", GameEngine::InputActionType::Pressed, GameEngine::InputCode::KB_UP, GameEngine::InputCode::GP_BUTTON_DPAD_UP);
        generalInput->SetActionMapping("SelectorDown", GameEngine::InputActionType::Pressed, GameEngine::InputCode::KB_DOWN, GameEngine::InputCode::GP_BUTTON_DPAD_DOWN);
        generalInput->SetActionMapping("SelectorConfirm", GameEngine::InputActionType::Pressed, GameEngine::InputCode::KB_X, GameEngine::InputCode::GP_BUTTON_SOUTH);
        generalInput->SetActionMapping("SkipRound", GameEngine::InputActionType::Pressed, GameEngine::InputCode::KB_F1, GameEngine::InputCode::GP_BUTTON_EAST);
        generalInput->SetActionMapping("MuteSound", GameEngine::InputActionType::Pressed, GameEngine::InputCode::KB_F2, GameEngine::InputCode::GP_BUTTON_NORTH);
        GameEngine::InputManager::Get().AddInputMapping("GeneralInput", std::move(generalInput));

        std::unique_ptr<GameEngine::InputMapping> player1InputMapping{ std::make_unique<GameEngine::InputMapping>() };
        player1InputMapping->SetActionMapping("MoveUp", GameEngine::InputActionType::Pressed, GameEngine::InputCode::KB_UP, GameEngine::InputCode::GP_BUTTON_DPAD_UP);
        player1InputMapping->SetActionMapping("MoveDown", GameEngine::InputActionType::Pressed, GameEngine::InputCode::KB_DOWN, GameEngine::InputCode::GP_BUTTON_DPAD_DOWN);
        player1InputMapping->SetActionMapping("MoveLeft", GameEngine::InputActionType::Pressed, GameEngine::InputCode::KB_LEFT, GameEngine::InputCode::GP_BUTTON_DPAD_LEFT);
        player1InputMapping->SetActionMapping("MoveRight", GameEngine::InputActionType::Pressed, GameEngine::InputCode::KB_RIGHT, GameEngine::InputCode::GP_BUTTON_DPAD_RIGHT);
        GameEngine::InputManager::Get().AddInputMapping("Player1", std::move(player1InputMapping));

        std::unique_ptr<GameEngine::InputMapping> player2InputMapping{ std::make_unique<GameEngine::InputMapping>() };
        player2InputMapping->SetActionMapping("MoveUp", GameEngine::InputActionType::Pressed, GameEngine::InputCode::NONE, GameEngine::InputCode::GP_BUTTON_DPAD_UP);
        player2InputMapping->SetActionMapping("MoveDown", GameEngine::InputActionType::Pressed, GameEngine::InputCode::NONE, GameEngine::InputCode::GP_BUTTON_DPAD_DOWN);
        player2InputMapping->SetActionMapping("MoveLeft", GameEngine::InputActionType::Pressed, GameEngine::InputCode::NONE, GameEngine::InputCode::GP_BUTTON_DPAD_LEFT);
        player2InputMapping->SetActionMapping("MoveRight", GameEngine::InputActionType::Pressed, GameEngine::InputCode::NONE, GameEngine::InputCode::GP_BUTTON_DPAD_RIGHT);
        GameEngine::InputManager::Get().AddInputMapping("Player2", std::move(player2InputMapping));

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
