#ifndef HEALTH_DISPLAY_H
#define HEALTH_DISPLAY_H

#include <Engine/Components/BaseComponent.h>
#include <Engine/Decoupling/Observer.h>
#include <Engine/Components/TextComponent.h>

#include <string>
#include <vector>

namespace Game
{
    class HealthComponent;

    class HealthDisplayObserver final: public GameEngine::Observer
    {
    private:
        GameEngine::TextComponent* m_pTextComponent;
        HealthComponent* m_pHealthComponent;
        std::string m_PlayerName;

    public:
        void OnNotify(GameEngine::GameObject&, std::string eventId);
        void SetPlayerName(std::string const& prefix);

        HealthDisplayObserver(GameEngine::TextComponent* pTextComponent, HealthComponent* pHealthComponent);
        ~HealthDisplayObserver() override = default;
    };

    class HealthComponent final : public GameEngine::BaseComponent
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

        HealthComponent(GameEngine::GameObject* owner);
        ~HealthComponent() override = default;
    };

    //class HealthDisplayComponent final : public GameEngine::BaseComponent
    //{
    //private:
    //    GameEngine::TextComponent m_Text;

    //public:
    //#pragma region BaseClassFunctions
    //    void FixedUpdate();
    //    void Update();
    //    void Render(glm::vec3 const&) const;
    //#pragma endregion
    //};
}

#endif
