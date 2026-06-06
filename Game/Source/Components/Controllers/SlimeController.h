#ifndef SLIME_CONTROLLER_H
#define SLIME_CONTROLLER_H

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Decoupling/Event.h>
#include <Engine/Misc/Types.h>

#include <Commands/PlayerCommands.h>
#include <Components/BaseCreature.h>
#include <Misc/Enums.h>
#include <Misc/Types.h>

#include <chrono>
#include <memory>
#include <queue>
#include <random>
#include <vector>

namespace Game
{
    namespace EnemyFunctions
    {
        inline void GenerateRandomPath(int pathSize, MovePath& path, std::vector<Direction> const& allowDirections)
        {
            std::mt19937 rng{ static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()) };

            for (int i = 0; i < pathSize; ++i)
            {
                auto randomIndex{ rng() % allowDirections.size() };
                auto direction{ static_cast<Direction>(allowDirections[randomIndex])};
                path.push(std::make_unique<EventArgMove>(EventArgMove{ "OnMove", MovementEvent::OnIdleWait, direction }));
                path.push(std::make_unique<EventArgMove>(EventArgMove{ "OnMove", MovementEvent::OnHop, direction }));
            }
        }
    }

    class GenericEnemyController final : public GameEngine::BaseComponent
    {
    private:
        MovePath m_Path{};

    public:
        void FixedUpdate() override {};
        void Update() override {};
        void Render(vec2 const&) const override {};
        void OnEvent(GameEngine::EventArg* eventArg) override;

        void Init(Creature creatureType);
        GenericEnemyController(GameEngine::GameObject* owner);
        ~GenericEnemyController() override = default;
    };
}

#endif