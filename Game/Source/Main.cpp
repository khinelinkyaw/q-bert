#include <Engine/Components/TextureComponent.h>
#include <Engine/Input/InputManager.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Core/Scene.h>
#include <Engine/Core/SceneManager.h>
#include <Engine/Input/InputMapping.h>
#include <Engine/Misc/Enums.h>
#include <Engine/Core/Minigin.h>

#include <Components/Qbert.h>
#include <Map/Graph.h>
#include <Components/ControllerComponent.h>

#include <memory>
#include <utility>

namespace Game
{
    inline static void load()
    {
        int constexpr screenWidth{ 400 };
        int constexpr screenHeight{ 400 };

        auto& scene = GameEngine::SceneManager::Get().CreateScene();

        //auto obj = std::make_unique<GameEngine::GameObject>();
        //obj->AddComponent<GameEngine::TextureComponent>()->SetTexture("cubes.png");
        //obj->SetPosition(75.f, 75.f);
        //scene.Add(std::move(obj));

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
        auto pPlayer1Comp{ player1->AddComponent<QBert>() };
        pPlayer1Comp->SetName("Player 1");
        player1->SetPosition(180.f, 63.f);
        scene.Add(std::move(player1));

        auto obj = std::make_unique<GameEngine::GameObject>();
        obj->AddComponent<Graph>();
        obj->SetPosition(screenWidth/2.f, 100.f);
        scene.Add(std::move(obj));

        GameEngine::Minigin::SetGameScreenSize(screenWidth, screenHeight);
    }
}

int main(int, char* [])
{
    GameEngine::RunGame(Game::load);
    return 0;
}
