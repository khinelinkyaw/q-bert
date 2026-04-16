#include <Engine/Components/ControllerComponent.h>
#include <Engine/Components/FrameCounterComponent.h>
#include <Engine/Components/TextComponent.h>
#include <Engine/Components/TextureComponent.h>
#include <Engine/Input/InputDevice.h>
#include <Engine/Input/InputManager.h>
#include <Engine/Misc/GameObject.h>
#include <Engine/Scene.h>
#include <Engine/SceneManager.h>

#include <Game/Components/Observers.h>
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
        go->AddComponent<GameEngine::FrameCounterComponent>();
        go->SetPosition(20, 20);
        scene.Add(std::move(go));

        go = std::make_unique<GameEngine::GameObject>();
        go->AddComponent<GameEngine::TextureComponent>()->SetTexture("my_guy.png");
        go->AddComponent<GameEngine::ControllerComponent>();
        auto pPlayer1Comp{ go->AddComponent<PlayerComponent>() };
        pPlayer1Comp->SetName("Player 1");
        //go->AddComponent<HealthComponent>();
        GameEngine::InputManager::GetInstance().RegisterController(go->GetComponent<GameEngine::ControllerComponent>(), GameEngine::InputDeviceType::Keyboard);
        go->SetPosition(500, 500);
        scene.Add(std::move(go));

        go = std::make_unique<GameEngine::GameObject>();
        go->AddComponent<GameEngine::TextureComponent>()->SetTexture("another_guy.png");
        go->AddComponent<GameEngine::ControllerComponent>()->SetSpeed(300.f);
        auto pPlayer2Comp{ go->AddComponent<PlayerComponent>() };
        pPlayer2Comp->SetName("Player 2");
        GameEngine::InputManager::GetInstance().RegisterController(go->GetComponent<GameEngine::ControllerComponent>(), GameEngine::InputDeviceType::Gamepad);
        go->SetPosition(600, 500);
        scene.Add(std::move(go));

        go = std::make_unique<GameEngine::GameObject>();
        go->SetPosition(20, 70);
        auto pP1TextComp{ go->AddComponent<GameEngine::TextComponent>() };
        auto pP1HealthObserver{ std::make_unique<HealthDisplayObserver>(pP1TextComp, pPlayer1Comp) };
        pPlayer1Comp->AddObserver(pP1HealthObserver.get());
        pP1TextComp->SetObserver(std::move(pP1HealthObserver));
        pPlayer1Comp->Init(3, 3);
        scene.Add(std::move(go));

        go = std::make_unique<GameEngine::GameObject>();
        go->SetPosition(20, 100);
        pP1TextComp = go->AddComponent<GameEngine::TextComponent>();
        auto pP1ScoreObserver{ std::make_unique<ScoreDisplayObserver>(pP1TextComp, pPlayer1Comp) };
        pPlayer1Comp->AddObserver(pP1ScoreObserver.get());
        pP1TextComp->SetObserver(std::move(pP1ScoreObserver));
        pPlayer1Comp->Init(3, 3);
        scene.Add(std::move(go));

        go = std::make_unique<GameEngine::GameObject>();
        go->SetPosition(500, 70);
        auto pP2TextComp{ go->AddComponent<GameEngine::TextComponent>() };
        auto pP2HealthObserver{ std::make_unique<HealthDisplayObserver>(pP2TextComp, pPlayer2Comp) };
        pPlayer2Comp->AddObserver(pP2HealthObserver.get());
        pP2TextComp->SetObserver(std::move(pP2HealthObserver));
        pPlayer2Comp->Init(3, 3);
        scene.Add(std::move(go));

        go = std::make_unique<GameEngine::GameObject>();
        go->SetPosition(500, 100);
        pP2TextComp = go->AddComponent<GameEngine::TextComponent>();
        auto pP2ScoreObserver{ std::make_unique<ScoreDisplayObserver>(pP2TextComp, pPlayer2Comp) };
        pPlayer2Comp->AddObserver(pP2ScoreObserver.get());
        pP2TextComp->SetObserver(std::move(pP2ScoreObserver));
        pPlayer2Comp->Init(3, 3);
        scene.Add(std::move(go));
    }
}
