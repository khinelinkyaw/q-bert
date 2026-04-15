#include <Engine/SceneManager.h>
#include <Engine/Input/InputManager.h>
#include <Engine/Input/InputDevice.h>
#include <Engine/Components/FrameCounterComponent.h>
#include <Engine/Components/TextureComponent.h>
#include <Engine/Components/ControllerComponent.h>
#include <Engine/Components/TextComponent.h>
#include <Engine/Scene.h>
#include <Engine/Misc/GameObject.h>

#include <Game/Components/HealthDisplay.h>
#include <Game/Components/PlayerComponent.h>

#include <memory>
#include <utility>

namespace Game
{
    inline void load()
    {
        auto& scene = GameEngine::SceneManager::GetInstance().CreateScene();

        auto go = std::make_unique<GameEngine::GameObject>();
        go->AddComponent<GameEngine::TextureComponent>()->SetTexture("background.png");
        scene.Add(std::move(go));

        go = std::make_unique<GameEngine::GameObject>();
        go->AddComponent<GameEngine::TextureComponent>()->SetTexture("logo.png");
        go->SetPosition(358, 180);
        scene.Add(std::move(go));

        go = std::make_unique<GameEngine::GameObject>();
        go->AddComponent<GameEngine::TextComponent>()->SetText("Programming 4 Assignment");
        go->SetPosition(292, 20);
        go->GetComponent<GameEngine::TextComponent>()->SetColor({ 255, 255, 0, 255 });
        scene.Add(std::move(go));

        go = std::make_unique<GameEngine::GameObject>();
        go->AddComponent<GameEngine::TextureComponent>()->SetTexture("my_guy.png");
        go->AddComponent<GameEngine::ControllerComponent>();
        auto pHealthComp{ go->AddComponent<PlayerComponent>() };
        //go->AddComponent<HealthComponent>();
        GameEngine::InputManager::GetInstance().RegisterController(go->GetComponent<GameEngine::ControllerComponent>(), GameEngine::InputDeviceType::Keyboard);
        go->SetPosition(500, 500);
        scene.Add(std::move(go));

        go = std::make_unique<GameEngine::GameObject>();
        go->AddComponent<GameEngine::TextureComponent>()->SetTexture("another_guy.png");
        go->AddComponent<GameEngine::ControllerComponent>()->SetSpeed(300.f);
        GameEngine::InputManager::GetInstance().RegisterController(go->GetComponent<GameEngine::ControllerComponent>(), GameEngine::InputDeviceType::Gamepad);
        go->SetPosition(600, 500);
        scene.Add(std::move(go));

        go = std::make_unique<GameEngine::GameObject>();
        go->AddComponent<GameEngine::FrameCounterComponent>();
        go->SetPosition(20, 20);
        scene.Add(std::move(go));

        go = std::make_unique<GameEngine::GameObject>();
        go->SetPosition(20, 70);
        auto pTextComp{ go->AddComponent<GameEngine::TextComponent>() };
        auto pHealthObserver{ std::make_unique<HealthDisplayObserver>(pTextComp, pHealthComp) };
        pHealthObserver->SetPlayerName("Player 1");
        pHealthComp->AddObserver(pHealthObserver.get());
        pTextComp->SetObserver(std::move(pHealthObserver));
        pHealthComp->Init(3, 3);
        scene.Add(std::move(go));
    }
}
