#ifndef HEALTH_COMPONENT_H
#define HEALTH_COMPONENT_H

#include "BaseComponent.h"

namespace Game
{
    class HealthComponent final : public Engine::BaseComponent
    {
    private:
        bool m_IsDead;
        int m_Health;
        int m_MaxHealth;

        void CheckHealth();
    public:
#pragma region BaseClassFunctions
        virtual void FixedUpdate();
        virtual void Update();
        virtual void Render(glm::vec3 const&) const;
#pragma endregion

        void TakeDamage(unsigned int damage);
        void Heal(unsigned int addedHealth);
        int GetHealth() const;
        void SetMaxHealth(unsigned int newMaxHealth);
        void Revive(unsigned int newHealth);
        void Revive();
        bool IsDead() const;

        HealthComponent(int health = 100, int maxHealth = 100);
    };
}


#endif
