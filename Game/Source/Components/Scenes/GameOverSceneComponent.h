#ifndef GAME_OVER_SCENE_COMPONENT_H
#define GAME_OVER_SCENE_COMPONENT_H

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Core/SceneManager.h>
#include <Engine/Events/EventArg.h>
#include <Engine/Misc/Types.h>

#include <UserInterface/UIEngine.h>
#include <utility>
#include <vector>

namespace Game
{
    enum class GameOverSelections
    {
        TryAgain = 0,
        HighScore = 1
    };

    class GameOverSceneComponent final : public GameEngine::BaseComponent
    {
    private:
        UIEngine m_UIEngine{ "JSON/GameOverUI.json" };
        std::vector<std::pair<GameOverSelections, GameEngine::GameObject*>> const m_SelectionElements{
            { GameOverSelections::TryAgain,   GameEngine::SceneManager::Get().GetActiveScene()->GetObjectByName("TryAgainUIElement")},
            { GameOverSelections::HighScore,   GameEngine::SceneManager::Get().GetActiveScene()->GetObjectByName("HighScoreUIElement") },
        };
        GameEngine::GameObject* m_pSelector{ GameEngine::SceneManager::Get().GetActiveScene()->GetObjectByName("SelectorUIElement") };
        int m_Selection{ 0 };

        void MoveSelector(int increment);

    public:
        void FixedUpdate() override {};
        void Update() override {};
        void Render(vec2 const&) const override {};
        void OnEvent(GameEngine::EventArg* eventArg) override;

        GameOverSceneComponent(GameEngine::GameObject* owner);
        ~GameOverSceneComponent() override = default;
    };
}

#endif
