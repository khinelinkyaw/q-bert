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
    static inline void load()
    {
        auto& scene = Engine::SceneManager::GetInstance().CreateScene();

        auto go = std::make_unique<Engine::GameObject>();
        go->AddComponent<Engine::TextureComponent>("background.png");
        scene.Add(std::move(go));

        go = std::make_unique<Engine::GameObject>();
        go->AddComponent<Engine::TextureComponent>("logo.png");
        go->SetPosition(358, 180);
        scene.Add(std::move(go));

        go = std::make_unique<Engine::GameObject>();
        go->AddComponent<Engine::TextComponent>("Programming 4 Assignment");
        go->SetPosition(292, 20);
        go->GetComponent<Engine::TextComponent>()->SetColor({ 255, 255, 0, 255 });
        scene.Add(std::move(go));

        go = std::make_unique<Engine::GameObject>();
        go->AddComponent<Engine::TextureComponent>("my_guy.png");
        go->AddComponent<Engine::ControllerComponent>(100.f);
        Engine::InputManager::GetInstance().RegisterController(go->GetComponent<Engine::ControllerComponent>(), Engine::InputDeviceType::Keyboard);
        go->SetPosition(500, 500);
        scene.Add(std::move(go));

        go = std::make_unique<Engine::GameObject>();
        go->AddComponent<Engine::TextureComponent>("another_guy.png");
        go->AddComponent<Engine::ControllerComponent>(300.f);
        Engine::InputManager::GetInstance().RegisterController(go->GetComponent<Engine::ControllerComponent>(), Engine::InputDeviceType::Gamepad);
        go->SetPosition(600, 500);
        scene.Add(std::move(go));

        go = std::make_unique<Engine::GameObject>();
        go->AddComponent<Engine::FrameCounterComponent>();
        go->SetPosition(20, 20);
        scene.Add(std::move(go));
    }
}
