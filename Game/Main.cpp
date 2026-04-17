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
#include <Game/AchievementSystem.h>

#include <memory>
#include <utility>

namespace Game
{
    inline void load()
    {
        auto& scene = GameEngine::SceneManager::GetInstance().CreateScene();

        auto obj = std::make_unique<GameEngine::GameObject>();
        obj->AddComponent<GameEngine::TextureComponent>()->SetTexture("background.png");
        scene.Add(std::move(obj));

        obj = std::make_unique<GameEngine::GameObject>();
        obj->AddComponent<GameEngine::TextureComponent>()->SetTexture("logo.png");
        obj->SetPosition(358, 180);
        scene.Add(std::move(obj));

        obj = std::make_unique<GameEngine::GameObject>();
        obj->AddComponent<GameEngine::TextComponent>()->SetText("Programming 4 Assignment");
        obj->SetPosition(292, 20);
        obj->GetComponent<GameEngine::TextComponent>()->SetColor({ 255, 255, 0, 255 });
        scene.Add(std::move(obj));

        obj = std::make_unique<GameEngine::GameObject>();
        obj->AddComponent<GameEngine::FrameCounterComponent>();
        obj->SetPosition(20, 20);
        scene.Add(std::move(obj));

        auto player1{ std::make_unique<GameEngine::GameObject>() };
        player1->AddComponent<GameEngine::TextureComponent>()->SetTexture("my_guy.png");
        player1->AddComponent<GameEngine::ControllerComponent>();
        auto pPlayer1Comp{ player1->AddComponent<PlayerComponent>() };
        pPlayer1Comp->SetName("Player 1");
        //go->AddComponent<HealthComponent>();
        GameEngine::InputManager::GetInstance().RegisterController(player1->GetComponent<GameEngine::ControllerComponent>(), GameEngine::InputDeviceType::Keyboard);
        player1->SetPosition(500, 500);

        auto player2{ std::make_unique<GameEngine::GameObject>() };
        player2->AddComponent<GameEngine::TextureComponent>()->SetTexture("another_guy.png");
        player2->AddComponent<GameEngine::ControllerComponent>()->SetSpeed(300.f);
        auto pPlayer2Comp{ player2->AddComponent<PlayerComponent>() };
        pPlayer2Comp->SetName("Player 2");
        GameEngine::InputManager::GetInstance().RegisterController(player2->GetComponent<GameEngine::ControllerComponent>(), GameEngine::InputDeviceType::Gamepad);
        player2->SetPosition(50, 50);
        player2->GetTransform()->SetParent(player1.get());

        scene.Add(std::move(player1));
        scene.Add(std::move(player2));

        obj = std::make_unique<GameEngine::GameObject>();
        obj->SetPosition(20, 70);
        auto pP1TextComp{ obj->AddComponent<GameEngine::TextComponent>() };
        auto pP1HealthObserver{ std::make_unique<HealthDisplayObserver>(pP1TextComp, pPlayer1Comp) };
        pPlayer1Comp->AddObserver(pP1HealthObserver.get());
        pP1TextComp->SetObserver(std::move(pP1HealthObserver));
        pPlayer1Comp->Init(3, 3);
        scene.Add(std::move(obj));

        obj = std::make_unique<GameEngine::GameObject>();
        obj->SetPosition(20, 100);
        pP1TextComp = obj->AddComponent<GameEngine::TextComponent>();
        auto pP1ScoreObserver{ std::make_unique<ScoreDisplayObserver>(pP1TextComp, pPlayer1Comp) };
        pPlayer1Comp->AddObserver(pP1ScoreObserver.get());
        pP1TextComp->SetObserver(std::move(pP1ScoreObserver));
        pPlayer1Comp->Init(3, 3);
        scene.Add(std::move(obj));

        obj = std::make_unique<GameEngine::GameObject>();
        obj->SetPosition(500, 70);
        auto pP2TextComp{ obj->AddComponent<GameEngine::TextComponent>() };
        auto pP2HealthObserver{ std::make_unique<HealthDisplayObserver>(pP2TextComp, pPlayer2Comp) };
        pPlayer2Comp->AddObserver(pP2HealthObserver.get());
        pP2TextComp->SetObserver(std::move(pP2HealthObserver));
        pPlayer2Comp->Init(3, 3);
        scene.Add(std::move(obj));

        obj = std::make_unique<GameEngine::GameObject>();
        obj->SetPosition(500, 100);
        pP2TextComp = obj->AddComponent<GameEngine::TextComponent>();
        auto pP2ScoreObserver{ std::make_unique<ScoreDisplayObserver>(pP2TextComp, pPlayer2Comp) };
        pPlayer2Comp->AddObserver(pP2ScoreObserver.get());
        pP2TextComp->SetObserver(std::move(pP2ScoreObserver));
        pPlayer2Comp->Init(3, 3);
        scene.Add(std::move(obj));

        auto achievementObj{ CreateAchievementObject() };
        pPlayer1Comp->AddObserver(achievementObj->GetComponent<AchievementComponent>()->GetAchievementSystem());
        scene.Add(std::move(achievementObj));
    }
}
