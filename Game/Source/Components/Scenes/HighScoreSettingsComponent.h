#ifndef HIGH_SCORE_SETTINGS_COMPONENT_H
#define HIGH_SCORE_SETTINGS_COMPONENT_H

#include <UserInterface/UIEngine.h>

#include <Engine/Components/BaseComponent.h>

namespace Game
{
    class HighScoreSettingsComponent final : public GameEngine::BaseComponent
    {
    private:
        UIEngine m_UIEngine{ "JSON/HighScoreUI.json" };

    public:
        void FixedUpdate() override {};
        void Update() override {};
        void Render(vec2 const&) const override {};

        HighScoreSettingsComponent(GameEngine::GameObject* owner);
        ~HighScoreSettingsComponent() override = default;
    };
}

#endif
