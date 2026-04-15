#ifndef PLAYER_COMPONENT_H
#define PLAYER_COMPONENT_H

#include <Engine/Components/BaseComponent.h>
#include <Engine/Decoupling/Observer.h>

#include <string>
#include <vector>

namespace Game
{
    class GameObject;

    class PlayerComponent final : public GameEngine::BaseComponent
    {
    private:
        bool m_IsDead;
        int m_Health;
        int m_MaxHealth;
        int m_Score;
        std::string m_Name;
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

        void SetName(std::string const& name);
        std::string GetName() const;

        int GetScore() const;
        void IncrementScore(int increment);

        void AddObserver(GameEngine::Observer* pObserver);
        void NotifyObservers(std::string eventId);
        void Init(int health, int maxHealth);

        PlayerComponent(GameEngine::GameObject* owner);
        ~PlayerComponent() override = default;
    };
}

#endif
