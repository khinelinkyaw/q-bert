#ifndef PLAYER_COMPONENT_H
#define PLAYER_COMPONENT_H

#include <Engine/Components/BaseComponent.h>
#include <Engine/Decoupling/Observer.h>

#include <vector>

namespace Game
{
    class PlayerComponent final : public GameEngine::BaseComponent
    {
    private:
        bool m_IsDead;
        int m_Health;
        int m_MaxHealth;
        std::vector<GameEngine::Observer*> m_pObservers;

        void CheckHealth();
    public:
#pragma region BaseClassFunctions
        void FixedUpdate() {};
        void Update() {};
        void Render(glm::vec3 const&) const {};
#pragma endregion

        void TakeDamage();
        void Heal();
        int GetHealth() const;
        void SetMaxHealth(int newMaxHealth);
        void Revive(int newHealth);
        void Revive();
        bool IsDead() const;

        void AddObserver(GameEngine::Observer* pObserver);
        void NotifyObservers(std::string eventId);
        void Init(int health, int maxHealth);

        PlayerComponent(GameEngine::GameObject* owner);
        ~PlayerComponent() override = default;
    };
}

#endif
