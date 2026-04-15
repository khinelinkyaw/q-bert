#ifndef OBSERVERS_H
#define OBSERVERS_H

#include <Engine/Components/TextComponent.h>
#include <Engine/Decoupling/Observer.h>

#include <Engine/Components/BaseComponent.h>
#include <string>

namespace Game
{
    class PlayerComponent;

    class HealthDisplayObserver final: public GameEngine::Observer
    {
    private:
        GameEngine::TextComponent* m_pTextComponent;
        PlayerComponent* m_pPlayerComponent;

    public:
        void OnNotify(GameEngine::GameObject&, std::string eventId);

        HealthDisplayObserver(GameEngine::TextComponent* pTextComponent, PlayerComponent* pPlayerComponent);
        ~HealthDisplayObserver() override = default;
    };

    class ScoreDisplayObserver final : public GameEngine::Observer
    {
    private:
        GameEngine::TextComponent* m_pTextComponent;
        PlayerComponent* m_pPlayerComponent;

    public:
        void OnNotify(GameEngine::GameObject&, std::string eventId);

        ScoreDisplayObserver(GameEngine::TextComponent* pTextComponent, PlayerComponent* pPlayerComponent);
        ~ScoreDisplayObserver() override = default;
    };
}

#endif
