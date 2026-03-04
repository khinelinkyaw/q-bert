#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "Components/FrameCounterComponent.h"
#include "Components/TextureComponent.h"
#include "Scene.h"
#include <filesystem>
#include <memory>
#include "Modules/GameObject.h"
#include <utility>
#include "Components/TextComponent.h"

namespace fs = std::filesystem;

static void load()
{
    auto& scene = dae::SceneManager::GetInstance().CreateScene();

    auto go = std::make_unique<dae::GameObject>();
    go->AddComponent<dae::TextureComponent>("background.png");
    scene.Add(std::move(go));

    go = std::make_unique<dae::GameObject>();
    go->AddComponent<dae::TextureComponent>("logo.png");
    go->SetPosition(358, 180);
    scene.Add(std::move(go));

    go = std::make_unique<dae::GameObject>();
    go->AddComponent<dae::TextComponent>("Programming 4 Assignment");
    go->SetPosition(292, 20);
    go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 0, 255 });
    scene.Add(std::move(go));

    go = std::make_unique<dae::GameObject>();
    go->AddComponent<dae::FrameCounterComponent>();
    go->SetPosition(20, 20);
    scene.Add(std::move(go));
}

int main(int, char* [])
{
#if __EMSCRIPTEN__
    fs::path data_location = "";
#else
    fs::path data_location = "./Data/";
    if (!fs::exists(data_location))
        data_location = "../Data/";
#endif
    dae::Minigin engine(data_location);
    engine.Run(load);
    return 0;
}
