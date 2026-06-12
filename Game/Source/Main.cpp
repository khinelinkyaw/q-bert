#include <Engine/Core/GameObject.h>
#include <Engine/Core/Minigin.h>
#include <Engine/Core/Scene.h>
#include <Engine/Core/SceneManager.h>

#include <Misc/Constants.h>
#include <Components/Scenes/GameplaySettingsComponent.h>

namespace Game
{
    inline static void load()
    {
        auto& scene = GameEngine::SceneManager::Get().CreateScene("Gameplay");
        auto& gameplaySettingsObj{ scene.CreateGameObject("GameplaySettings") };
        gameplaySettingsObj.AddComponent<GameplaySettingsComponent>()->Init("JSON/Levels.json");

        GameEngine::Minigin::SetGameScreenSize(Screen::GAME_WIDTH, Screen::GAME_HEIGHT);
        GameEngine::Minigin::MaximizeWindow();
    }
}

int main(int, char* [])
{
    GameEngine::RunGame(Game::load);
    return 0;
}
