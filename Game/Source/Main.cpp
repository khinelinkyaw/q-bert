#include <Engine/Animation/Animation.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Core/Minigin.h>
#include <Engine/Core/Scene.h>
#include <Engine/Core/SceneManager.h>
#include <Engine/Input/InputManager.h>
#include <Engine/Input/InputMapping.h>
#include <Engine/Misc/Enums.h>
#include <Engine/Components/TextureComponent.h>

#include <Components/BaseCreature.h>
#include <Components/Controllers/ControllerComponent.h>
#include <Map/Graph.h>

#include <memory>
#include <utility>

namespace Game
{
    inline static void load()
    {
        int constexpr screenWidth{ 400 };
        int constexpr screenHeight{ 400 };

        auto& scene = GameEngine::SceneManager::Get().CreateScene("Gameplay");

        std::unique_ptr<GameEngine::InputMapping> playerInputMapping{ std::make_unique<GameEngine::InputMapping>() };
        playerInputMapping->SetActionMapping("MoveUp", GameEngine::InputActionType::Pressed, GameEngine::InputCode::KB_UP, GameEngine::InputCode::GP_BUTTON_DPAD_UP);
        playerInputMapping->SetActionMapping("MoveDown", GameEngine::InputActionType::Pressed, GameEngine::InputCode::KB_DOWN, GameEngine::InputCode::GP_BUTTON_DPAD_DOWN);
        playerInputMapping->SetActionMapping("MoveLeft", GameEngine::InputActionType::Pressed, GameEngine::InputCode::KB_LEFT, GameEngine::InputCode::GP_BUTTON_DPAD_LEFT);
        playerInputMapping->SetActionMapping("MoveRight", GameEngine::InputActionType::Pressed, GameEngine::InputCode::KB_RIGHT, GameEngine::InputCode::GP_BUTTON_DPAD_RIGHT);

        auto inputMapping{ GameEngine::InputManager::Get().AddInputMapping("Player", std::move(playerInputMapping)) };

        auto& graphObj{ scene.CreateGameObject() };
        auto graphComp{ graphObj.AddComponent<Graph>() };
        graphObj.GetTransform()->SetLocalPosition(screenWidth / 2.f, 100.f);

        auto& player1{ scene.CreateGameObject() };
        auto creatureComp{ player1.AddComponent<BaseCreature>() };
        creatureComp->Init(Creature::QBert);
        player1.GetTransform()->SetLocalPosition(graphComp->GetBlockSurfaceCenter(4));
        auto playerController{ player1.AddComponent<ControllerComponent>() };
        playerController->Init(inputMapping, &GameEngine::InputManager::Get().GetKeyboardInputDevice());

        auto& slime{ scene.CreateGameObject() };
        slime.GetTransform()->SetLocalPosition(graphComp->GetBlockSurfaceCenter(7));
        slime.AddComponent<BaseCreature>()->Init(Creature::PurpleSlime);

        GameEngine::Minigin::SetGameScreenSize(screenWidth, screenHeight);
        GameEngine::Minigin::MaximizeWindow();
    }
}

int main(int, char* [])
{
    GameEngine::RunGame(Game::load);
    return 0;
}
