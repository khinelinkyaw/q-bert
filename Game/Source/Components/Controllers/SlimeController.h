#ifndef SLIME_CONTROLLER_H
#define SLIME_CONTROLLER_H

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Decoupling/Event.h>
#include <Engine/Misc/Types.h>

#include <Characters/MovementState.h>
#include <Commands/PlayerCommands.h>
#include <Components/BaseCreature.h>
#include <Misc/Types.h>

#include <chrono>
#include <memory>
#include <queue>
#include <random>

namespace Game
{
    namespace SlimeFunctions
    {
        inline void GenerateRandomPath(int pathSize, MovePath& path)
        {
            std::mt19937 rng{ static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()) };

            for (int i = 0; i < pathSize; ++i)
            {
                auto direction{ static_cast<Direction>((rng() % 2) + 2) };
                path.push(std::make_unique<EventArgMove>(EventArgMove{ "OnMove", MovementEvent::OnIdleWait, direction }));
                path.push(std::make_unique<EventArgMove>(EventArgMove{ "OnMove", MovementEvent::OnHop, direction }));
            }
        }
    }

    class SlimeController final : public GameEngine::BaseComponent
    {
    private:
        MovePath m_Path{};

    public:
        void FixedUpdate() override {};
        void Update() override {};
        void Render(vec3 const&) const override {};
        void OnEvent(GameEngine::EventArg* eventArg) override;

        void Init(Creature creatureType);
        SlimeController(GameEngine::GameObject* owner);
        ~SlimeController() override = default;
    };
}

#endif