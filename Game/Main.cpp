#include <Engine/SceneManager.h>
#include <Engine/InputManager.h>
#include <Engine/Components/FrameCounterComponent.h>
#include <Engine/Components/TextureComponent.h>
#include <Engine/Components/ControllerComponent.h>
#include <Engine/Scene.h>
#include <memory>
#include <Engine/Utils/GameObject.h>
#include <utility>
#include <Engine/Components/TextComponent.h>
#include <Engine/InputDevice.h>

namespace Game
{
    inline void load()
    {
        auto& scene = GameEngine::SceneManager::GetInstance().CreateScene();

        auto go = std::make_unique<GameEngine::GameObject>();
        go->AddComponent<GameEngine::TextureComponent>("background.png");
        scene.Add(std::move(go));

        go = std::make_unique<GameEngine::GameObject>();
        go->AddComponent<GameEngine::TextureComponent>("logo.png");
        go->SetPosition(358, 180);
        scene.Add(std::move(go));

        go = std::make_unique<GameEngine::GameObject>();
        go->AddComponent<GameEngine::TextComponent>("Programming 4 Assignment");
        go->SetPosition(292, 20);
        go->GetComponent<GameEngine::TextComponent>()->SetColor({ 255, 255, 0, 255 });
        scene.Add(std::move(go));

        go = std::make_unique<GameEngine::GameObject>();
        go->AddComponent<GameEngine::TextureComponent>("my_guy.png");
        go->AddComponent<GameEngine::ControllerComponent>(100.f);
        GameEngine::InputManager::GetInstance().RegisterController(go->GetComponent<GameEngine::ControllerComponent>(), GameEngine::InputDeviceType::Keyboard);
        go->SetPosition(500, 500);
        scene.Add(std::move(go));

        go = std::make_unique<GameEngine::GameObject>();
        go->AddComponent<GameEngine::TextureComponent>("another_guy.png");
        go->AddComponent<GameEngine::ControllerComponent>(300.f);
        GameEngine::InputManager::GetInstance().RegisterController(go->GetComponent<GameEngine::ControllerComponent>(), GameEngine::InputDeviceType::Gamepad);
        go->SetPosition(600, 500);
        scene.Add(std::move(go));

        go = std::make_unique<GameEngine::GameObject>();
        go->AddComponent<GameEngine::FrameCounterComponent>();
        go->SetPosition(20, 20);
        scene.Add(std::move(go));
    }
}
