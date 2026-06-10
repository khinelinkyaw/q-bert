#ifndef SCORE_COUNTER_COMPONENT_H
#define SCORE_COUNTER_COMPONENT_H

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Events/EventArg.h>
#include <Engine/Misc/Types.h>

#include <Components/SpriteFontComponent.h>
#include <Misc/Enums.h>

namespace Game
{
    class ScoreCounterComponent final : public GameEngine::BaseComponent
    {
    private:
        SpriteFontComponent* m_pPlayerScoreTextComponent{};

    public:
        void FixedUpdate() override {};
        void Update() override {};
        void Render(vec2 const& ) const override {};
        void OnEvent(GameEngine::EventArg* eventArg) override;

        void Init(PlayerIndex playerIndex = PlayerIndex::Player1);
        ScoreCounterComponent(GameEngine::GameObject* owner);
        ~ScoreCounterComponent() override = default;
    };
}

#endif
