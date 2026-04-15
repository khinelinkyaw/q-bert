#ifndef HEALTH_DISPLAY_H
#define HEALTH_DISPLAY_H

#include <Engine/Decoupling/Observer.h>
#include <Engine/Components/TextComponent.h>

#include <string>

namespace Game
{
    class GameObject;
    class PlayerComponent;

    class HealthDisplayObserver final: public GameEngine::Observer
    {
    private:
        GameEngine::TextComponent* m_pTextComponent;
        PlayerComponent* m_pPlayerComponent;
        std::string m_PlayerName;

    public:
        void OnNotify(GameEngine::GameObject&, std::string eventId);
        void SetPlayerName(std::string const& prefix);

        HealthDisplayObserver(GameEngine::TextComponent* pTextComponent, PlayerComponent* pHealthComponent);
        ~HealthDisplayObserver() override = default;
    };
}

#endif
