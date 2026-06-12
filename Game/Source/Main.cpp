#include <Engine/Core/Minigin.h>
#include <Engine/Core/SceneManager.h>

#include <Components/Scenes/GameplaySettingsComponent.h>
#include <Misc/Constants.h>

#include <Engine/Input/InputManager.h>
#include <Engine/Input/InputMapping.h>

#include <Engine/Misc/Enums.h>
#include <SDL3/SDL_main.h>
#include <memory>
#include <utility>
#include <Components/Scenes/StartMenuSettingsComponent.h>
#include <Components/Controllers/GeneralInputControllerComponent.h>

namespace Game
{
    inline static void load()
    {
        std::unique_ptr<GameEngine::InputMapping> generalInput{ std::make_unique<GameEngine::InputMapping>() };
        generalInput->SetActionMapping("SelectorUp", GameEngine::InputActionType::Pressed, GameEngine::InputCode::KB_UP, GameEngine::InputCode::GP_BUTTON_DPAD_UP);
        generalInput->SetActionMapping("SelectorDown", GameEngine::InputActionType::Pressed, GameEngine::InputCode::KB_DOWN, GameEngine::InputCode::GP_BUTTON_DPAD_DOWN);
        generalInput->SetActionMapping("SelectorConfirm", GameEngine::InputActionType::Pressed, GameEngine::InputCode::KB_X, GameEngine::InputCode::GP_BUTTON_SOUTH);
        generalInput->SetActionMapping("MuteSound", GameEngine::InputActionType::Pressed, GameEngine::InputCode::KB_Z, GameEngine::InputCode::GP_BUTTON_NORTH);
        generalInput->SetActionMapping("OnSkipRound", GameEngine::InputActionType::Pressed, GameEngine::InputCode::KB_S, GameEngine::InputCode::GP_BUTTON_EAST);
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

        auto& gameplayScene = GameEngine::SceneManager::Get().CreateScene("Gameplay");
        GameEngine::SceneManager::Get().SetActiveScene(&gameplayScene);
        auto& gameplaySettingsObj{ gameplayScene.CreateGameObject("GameplaySettings") };
        gameplaySettingsObj.AddComponent<GameplaySettingsComponent>();

        auto& mainMenuScene = GameEngine::SceneManager::Get().CreateScene("MainMenu");
        GameEngine::SceneManager::Get().SetActiveScene(&mainMenuScene);
        auto& mainMenuSettingsObj{ mainMenuScene.CreateGameObject("MainMenuSettings") };
        mainMenuSettingsObj.AddComponent<StartMenuSettingsComponent>();
        auto generalInputController{ mainMenuSettingsObj.AddComponent<GeneralInputController>() };
        generalInputController->AddInputDevice(&GameEngine::InputManager::Get().GetKeyboardInputDevice());
        generalInputController->AddInputDevice(&GameEngine::InputManager::Get().GetGamepadInputDevice(1));
        generalInputController->AddInputDevice(&GameEngine::InputManager::Get().GetGamepadInputDevice(2));
        generalInputController->SetInputMapping(GameEngine::InputManager::Get().GetInputMapping("GeneralInput"));

        GameEngine::Minigin::SetGameScreenSize(Screen::GAME_WIDTH, Screen::GAME_HEIGHT);
        GameEngine::Minigin::MaximizeWindow();
    }
}

int main(int, char* [])
{
    GameEngine::RunGame(Game::load);
    return 0;
}
