#include <Engine/Components/SpriteComponent.h>
#include <Engine/Components/SpriteAnimationComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Core/Minigin.h>
#include <Engine/Core/Scene.h>
#include <Engine/Core/SceneManager.h>
#include <Engine/Input/InputManager.h>
#include <Engine/Input/InputMapping.h>
#include <Engine/Misc/Enums.h>

#include <Components/CreatureSpawner.h>
#include <Creatures/CreatureFactory.h>
#include <Components/BaseCreature.h>
#include <Map/Graph.h>
#include <Misc/Constants.h>
#include <Components/Controllers/ControllerComponent.h>
#include <Components/SpriteFontComponent.h>
#include <UserInterface/UIEngine.h>

#include <memory>
#include <utility>

namespace Game
{
    inline static void load()
    {
        auto& scene = GameEngine::SceneManager::Get().CreateScene("Gameplay");

        std::unique_ptr<GameEngine::InputMapping> playerInputMapping{ std::make_unique<GameEngine::InputMapping>() };
        playerInputMapping->SetActionMapping("MoveUp", GameEngine::InputActionType::Pressed, GameEngine::InputCode::KB_UP, GameEngine::InputCode::GP_BUTTON_DPAD_UP);
        playerInputMapping->SetActionMapping("MoveDown", GameEngine::InputActionType::Pressed, GameEngine::InputCode::KB_DOWN, GameEngine::InputCode::GP_BUTTON_DPAD_DOWN);
        playerInputMapping->SetActionMapping("MoveLeft", GameEngine::InputActionType::Pressed, GameEngine::InputCode::KB_LEFT, GameEngine::InputCode::GP_BUTTON_DPAD_LEFT);
        playerInputMapping->SetActionMapping("MoveRight", GameEngine::InputActionType::Pressed, GameEngine::InputCode::KB_RIGHT, GameEngine::InputCode::GP_BUTTON_DPAD_RIGHT);

        auto inputMapping{ GameEngine::InputManager::Get().AddInputMapping("Player", std::move(playerInputMapping)) };

        auto& graphObj{ scene.CreateGameObject() };
        auto graphComp{ graphObj.AddComponent<Graph>() };
        graphObj.GetTransform()->SetLocalPosition(Screen::GAME_WIDTH / 2.f, 100.f);
        graphObj.GetTransform()->SetZIndex(-1);

        auto& player{ scene.CreateGameObject() };
        CreatureFactory::BuildCreatureComponents(player, Creature::QBert);
        player.GetTransform()->SetLocalPosition(graphComp->GetBlockSurfaceCenter(0, BlockSurface::Top));
        player.GetComponent<ControllerComponent>()->Init(inputMapping, &GameEngine::InputManager::Get().GetKeyboardInputDevice());

        auto& slimeSpawner{ scene.CreateGameObject() };
        slimeSpawner.AddComponent<CreatureSpawner>()->Init(Creature::PurpleSlime, 5.f);

        UIEngine uiEngine{};
        //auto& rootUI{ uiFactory.CreateUIElement() };
        //uiFactory.CreatePlayer1UIElements(rootUI);
        //uiFactory.CreateChangeToBlockUIElements();

        GameEngine::Minigin::SetGameScreenSize(Screen::GAME_WIDTH, Screen::GAME_HEIGHT);
        GameEngine::Minigin::MaximizeWindow();
    }
}

int main(int, char* [])
{
    GameEngine::RunGame(Game::load);
    return 0;
}
