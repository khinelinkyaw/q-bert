#include <Engine/Components/FrameCounterComponent.h>
#include <Engine/Components/TextureComponent.h>
#include <Engine/Input/InputManager.h>
#include <Engine/Misc/GameObject.h>
#include <Engine/Scene.h>
#include <Engine/SceneManager.h>
#include <Engine/Input/InputMapping.h>
#include <Engine/Misc/Enums.h>
#include <Engine/Minigin.h>

#include "Components/PlayerComponent.h"
#include "Components/ControllerComponent.h"

#include <memory>
#include <utility>

namespace Game
{
    inline void load()
    {
        int constexpr screenWidth{ 400 };
        int constexpr screenHeight{ 400 };

        auto& scene = GameEngine::SceneManager::Get().CreateScene();

        auto obj = std::make_unique<GameEngine::GameObject>();
        obj->AddComponent<GameEngine::TextureComponent>()->SetTexture("cubes.png");
        obj->SetPosition(75.f, 75.f);
        scene.Add(std::move(obj));

        obj = std::make_unique<GameEngine::GameObject>();
        obj->AddComponent<GameEngine::FrameCounterComponent>();
        obj->SetPosition(20.f, 20.f);
        scene.Add(std::move(obj));

        std::unique_ptr<GameEngine::InputMapping> playerInputMapping{ std::make_unique<GameEngine::InputMapping>() };
        playerInputMapping->SetActionMapping("MoveUp", GameEngine::InputActionType::Pressed, GameEngine::InputCode::KB_UP, GameEngine::InputCode::GP_BUTTON_DPAD_UP);
        playerInputMapping->SetActionMapping("MoveDown", GameEngine::InputActionType::Pressed, GameEngine::InputCode::KB_DOWN, GameEngine::InputCode::GP_BUTTON_DPAD_DOWN);
        playerInputMapping->SetActionMapping("MoveLeft", GameEngine::InputActionType::Pressed, GameEngine::InputCode::KB_LEFT, GameEngine::InputCode::GP_BUTTON_DPAD_LEFT);
        playerInputMapping->SetActionMapping("MoveRight", GameEngine::InputActionType::Pressed, GameEngine::InputCode::KB_RIGHT, GameEngine::InputCode::GP_BUTTON_DPAD_RIGHT);

        auto inputMapping{ GameEngine::InputManager::Get().AddInputMapping("Player", std::move(playerInputMapping)) };

        auto player1{ std::make_unique<GameEngine::GameObject>() };
        player1->AddComponent<GameEngine::TextureComponent>()->SetTexture("my_guy.png");
        auto p1Controller{ player1->AddComponent<ControllerComponent>() };
        p1Controller->Init(inputMapping, &GameEngine::InputManager::Get().GetKeyboardInputDevice());
        auto pPlayer1Comp{ player1->AddComponent<PlayerComponent>() };
        pPlayer1Comp->SetName("Player 1");
        player1->SetPosition(180.f, 63.f);
        scene.Add(std::move(player1));

        GameEngine::Minigin::SetGameScreenSize(screenWidth, screenHeight);
    }
}
