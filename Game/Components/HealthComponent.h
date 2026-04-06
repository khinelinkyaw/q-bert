#ifndef HEALTH_COMPONENT_H
#define HEALTH_COMPONENT_H

#include <Engine/Components/BaseComponent.h>

namespace GameEngine
{
    class MessageQueue;
}

namespace Game
{
    class HealthComponent final : public GameEngine::BaseComponent
    {
    private:
        bool m_IsDead;
        unsigned int m_Health;
        unsigned int m_MaxHealth;
        GameEngine::MessageQueue* m_MessageQueue;

        void CheckHealth();
    public:
#pragma region BaseClassFunctions
        void FixedUpdate();
        void Update();
        void Render(glm::vec3 const&) const;
#pragma endregion

        void TakeDamage();
        void Heal();
        int GetHealth() const;
        void SetMaxHealth(unsigned int newMaxHealth);
        void Revive(unsigned int newHealth);
        void Revive();
        bool IsDead() const;

        HealthComponent(GameEngine::MessageQueue* messageQueue, unsigned int health = 3, unsigned int maxHealth = 3);
    };
}

#endif
