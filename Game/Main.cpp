#include "SceneManager.h"
#include "InputManager.h"
#include "Components/FrameCounterComponent.h"
#include "Components/TextureComponent.h"
#include "Components/ControllerComponent.h"
#include "Scene.h"
#include <memory>
#include "Modules/GameObject.h"
#include <utility>
#include "Components/TextComponent.h"
#include "InputDevice.h"

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
