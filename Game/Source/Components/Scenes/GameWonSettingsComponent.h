#ifndef GAME_WON_SETTINGS_COMPONENT_H
#define GAME_WON_SETTINGS_COMPONENT_H

#include <Engine/UI/UIEngine.h>
#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Misc/Types.h>

namespace Game
{
    class GameWonSettingsComponent final : public GameEngine::BaseComponent
    {
    private:
        GameEngine::UIEngine m_UIEngine{ "JSON/GameWonUI.json" };

        float m_ElapsedTime{};
        float m_TransitionTime{5.f};

    public:
        void FixedUpdate() override {};
        void Update() override;
        void Render(vec2 const&) const override {};

        GameWonSettingsComponent(GameEngine::GameObject* owner);
        ~GameWonSettingsComponent() override = default;
    };
}

#endif
