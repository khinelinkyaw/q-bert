#ifndef SLIME_CONTROLLER_H
#define SLIME_CONTROLLER_H

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Events/EventArg.h>
#include <Engine/Misc/Types.h>
#include <Engine/Core/Random.h>

#include <Events/EventArgMove.h>
#include <Components/BaseCreature.h>
#include <Misc/Enums.h>
#include <Misc/Types.h>

#include <memory>
#include <queue>
#include <vector>

namespace Game
{
    namespace EnemyFunctions
    {
        inline void GenerateRandomPath(int pathSize, MovePath& path, std::vector<Direction> const& allowDirections)
        {
            auto& rng{ GameEngine::Random::GetRNG() };

            for (int i = 0; i < pathSize; ++i)
            {
                auto randomIndex{ rng() % allowDirections.size() };
                auto direction{ static_cast<Direction>(allowDirections[randomIndex])};
                path.push(std::make_unique<EventArgMove>(EventArgMove{ {"OnMove"}, MovementEvent::OnIdleWait, direction }));
                path.push(std::make_unique<EventArgMove>(EventArgMove{ {"OnMove"}, MovementEvent::OnHop, direction }));
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