#ifndef ACHIEVEMENT_SYSTEM_H
#define ACHIEVEMENT_SYSTEM_H

#include <Engine/Components/BaseComponent.h>
#include <Engine/Decoupling/Observer.h>
#include <Engine/Misc/GameObject.h>

#include <memory>
#include <string>

namespace Game
{
    class AchievementSystem final: public GameEngine::Observer
    {
    public:
        void OnNotify(GameEngine::GameObject&, std::string eventId) override;

        AchievementSystem();
        ~AchievementSystem() override = default;
    };

    class AchievementComponent final: public GameEngine::BaseComponent
    {
    private:
        AchievementSystem m_AchievementSystem;

    public:
        void FixedUpdate() override {};
        void Update() override {};
        void Render(glm::vec3 const&) const {};

        AchievementSystem* GetAchievementSystem() { return &m_AchievementSystem; };

        AchievementComponent(GameEngine::GameObject* owner);
        ~AchievementComponent() override = default;
    };

    inline std::unique_ptr<GameEngine::GameObject> CreateAchievementObject()
    {
        std::unique_ptr<GameEngine::GameObject> gameObject{ std::make_unique<GameEngine::GameObject>() };

        gameObject->AddComponent<AchievementComponent>();

        return gameObject;
    }
}

#endif
