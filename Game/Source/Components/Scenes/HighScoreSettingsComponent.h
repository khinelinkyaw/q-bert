#ifndef HIGH_SCORE_SETTINGS_COMPONENT_H
#define HIGH_SCORE_SETTINGS_COMPONENT_H

#include <Engine/UI/UIEngine.h>
#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Core/SceneManager.h>
#include <Engine/Events/EventArg.h>
#include <Engine/Misc/Types.h>

namespace Game
{
    class HighScoreSettingsComponent final : public GameEngine::BaseComponent
    {
    private:
        GameEngine::UIEngine m_UIEngine{ "JSON/HighScoreUI.json" };
        GameEngine::GameObject* m_ScoreboardTextObj{ GameEngine::SceneManager::Get().GetActiveScene()->GetObjectByName("PlayerScoresUIElement") };

    public:
        void FixedUpdate() override {};
        void Update() override {};
        void Render(vec2 const&) const override {};
        void OnEvent(GameEngine::EventArg* eventArg) override;
        void OnSceneLoad() override;

        HighScoreSettingsComponent(GameEngine::GameObject* owner);
        ~HighScoreSettingsComponent() override = default;
    };
}

#endif
