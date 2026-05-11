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

        std::unique_ptr<GameEngine::InputMapping> playerInputMapping{ std::make_unique<GameEngine::InputMapping>() };
        playerInputMapping->SetActionMapping("MoveUp", GameEngine::InputActionType::Pressed, GameEngine::InputCode::KB_UP, GameEngine::InputCode::GP_BUTTON_DPAD_UP);
        playerInputMapping->SetActionMapping("MoveDown", GameEngine::InputActionType::Pressed, GameEngine::InputCode::KB_DOWN, GameEngine::InputCode::GP_BUTTON_DPAD_DOWN);
        playerInputMapping->SetActionMapping("MoveLeft", GameEngine::InputActionType::Pressed, GameEngine::InputCode::KB_LEFT, GameEngine::InputCode::GP_BUTTON_DPAD_LEFT);
        playerInputMapping->SetActionMapping("MoveRight", GameEngine::InputActionType::Pressed, GameEngine::InputCode::KB_RIGHT, GameEngine::InputCode::GP_BUTTON_DPAD_RIGHT);

        auto inputMapping{ GameEngine::InputManager::Get().AddInputMapping("Player", std::move(playerInputMapping)) };

        auto obj = std::make_unique<GameEngine::GameObject>();
        auto graphComp{ obj->AddComponent<Graph>() };
        obj->SetLocationPosition(screenWidth / 2.f, 100.f);
        scene.Add(std::move(obj));

        auto player1{ std::make_unique<GameEngine::GameObject>() };
        player1->AddComponent<GameEngine::TextureComponent>()->SetTexture("my_guy.png");
        auto p1Controller{ player1->AddComponent<ControllerComponent>() };
        p1Controller->Init(inputMapping, &GameEngine::InputManager::Get().GetKeyboardInputDevice());
        auto pPlayer1Comp{ player1->AddComponent<QBert>() };
        pPlayer1Comp->SetName("Player 1");
        player1->SetLocationPosition(graphComp->GetBlockSurfaceCenter(0));
        scene.Add(std::move(player1));

        GameEngine::Minigin::SetGameScreenSize(screenWidth, screenHeight);
        GameEngine::Minigin::MaximizeWindow();
    }
}

int main(int, char* [])
{
    GameEngine::RunGame(Game::load);
    return 0;
}
