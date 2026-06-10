#ifndef SCORE_COUNTER_COMPONENT_H
#define SCORE_COUNTER_COMPONENT_H

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/SceneManager.h>

#include <UserInterface/UIEngine.h>
#include <Components/SpriteFontComponent.h>

namespace Game
{
    class ScoreCounterComponent final : public GameEngine::BaseComponent
    {
    private:
        SpriteFontComponent* m_pScoreTextComponent{
            GameEngine::SceneManager::Get().GetActiveScene()->GetObjectByName(GameplayUI::PLAYER_1_SCORE_ELEMENT)->GetComponent<SpriteFontComponent>()
        };

    public:
        void FixedUpdate() override {};
        void Update() override {};
        void Render(vec2 const& ) const override {};
        void OnEvent(GameEngine::EventArg* eventArg) override;

        ScoreCounterComponent(GameEngine::GameObject* owner);
        ~ScoreCounterComponent() override = default;
    };
}

#endif
