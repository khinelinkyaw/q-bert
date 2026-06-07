#include <Engine/Animation/Animation.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Core/Minigin.h>
#include <Engine/Core/Scene.h>
#include <Engine/Core/SceneManager.h>
#include <Engine/Input/InputManager.h>
#include <Engine/Input/InputMapping.h>
#include <Engine/Misc/Enums.h>

#include <Components/CreatureSpawner.h>
#include <Components/BaseCreature.h>
#include <Map/Graph.h>
#include <Components/Controllers/ControllerComponent.h>

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
        graphObj.GetTransform()->SetZIndex(-1);

        auto& player{ Builder::BuildQBert() };
        player.GetTransform()->SetLocalPosition(graphComp->GetBlockSurfaceCenter(0, BlockSurface::Top));
        //auto playerTexture{ player.GetComponent<GameEngine::TextureComponent>() };
        //playerTexture->SetRotation(135.0);
        //playerTexture->SetOriginOffset({ 2.f, 2.f });
        player.GetComponent<ControllerComponent>()->Init(inputMapping, &GameEngine::InputManager::Get().GetKeyboardInputDevice());

        auto& slime{ Builder::BuildPurpleSlime() };
        slime.GetTransform()->SetLocalPosition(graphComp->GetBlockSurfaceCenter(1, BlockSurface::Top));

        auto& ugg{ Builder::BuildUgg() };
        ugg.GetTransform()->SetLocalPosition(graphComp->GetBlockSurfaceCenter(27, BlockSurface::Right));

        auto& wrongway{ Builder::BuildWrongWay() };
        wrongway.GetTransform()->SetLocalPosition(graphComp->GetBlockSurfaceCenter(21, BlockSurface::Left));


        GameEngine::Minigin::SetGameScreenSize(screenWidth, screenHeight);
        GameEngine::Minigin::MaximizeWindow();
    }
}

int main(int, char* [])
{
    GameEngine::RunGame(Game::load);
    return 0;
}
