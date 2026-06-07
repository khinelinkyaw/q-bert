#ifndef QBERT_H
#define QBERT_H
//
//#include <Engine/Components/BaseComponent.h>
//#include <Engine/Core/GameObject.h>
//#include <Engine/Decoupling/Observer.h>
//#include <Engine/Events/EventArg.h>
//
//#include <Characters/MovementState.h>
//
//#include <memory>
//#include <string>
//#include <vector>

//namespace Game
//{
//    class QBert final : public GameEngine::BaseComponent
//    {
//    public:
//        static int constexpr STARTING_HEALTH{ 3 };
//
//    private:
//        bool m_IsDead{ false };
//        int m_Health{ STARTING_HEALTH };
//        int m_MaxHealth{ STARTING_HEALTH };
//        int m_Score{};
//        std::string m_Name{""};
//        std::vector<GameEngine::Observer*> m_pObservers{};
//        std::unique_ptr<MovementState> m_pMovementState{};
//
//        void CheckHealth();
//
//    public:
//#pragma region BaseClassFunctions
//        void FixedUpdate() override {};
//        void Update() override;
//        void Render(vec2 const&) const override {};
//#pragma endregion
//        void OnEvent(GameEngine::EventArg* eventArg) override;
//
//        void TakeDamage();
//        void Heal();
//        int GetHealth() const;
//        void SetMaxHealth(int newMaxHealth);
//        void Revive(int newHealth);
//        void Revive();
//        bool IsDead() const;
//
//        void SetName(std::string const& name);
//        std::string GetName() const;
//
//        int GetScore() const;
//        void IncrementScore(int increment);
//
//        void AddObserver(GameEngine::Observer* pObserver);
//        void NotifyObservers(std::string eventId);
//        void Init(int health, int maxHealth);
//
//        QBert(GameEngine::GameObject* owner);
//        ~QBert() override = default;
//    };
//}

#endif
