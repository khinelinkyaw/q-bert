#ifndef ENEMY_SPAWNER_H
#define ENEMY_SPAWNER_H

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Misc/Types.h>

#include <Misc/Enums.h>
#include <vector>

#include <nlohmann/detail/macro_scope.hpp>
#include <nlohmann/json.hpp>

namespace Game
{
    struct CreatureSpawnerInfo final
    {
        Creature CreatureType{};
        float SpawnInterval{ 5.f };
        int SpawnProbability{ 100 };
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(CreatureSpawnerInfo,
        CreatureType,
        SpawnInterval,
        SpawnProbability
    )

    class Graph;
    class CreatureSpawner final : public GameEngine::BaseComponent
    {
    private:
        static inline std::vector<int> const TOP_SPAWN_POINTS{ 1, 2 };
        static inline std::vector<int> const LEFT_SPAWN_POINTS{ 21 };
        static inline std::vector<int> const RIGHT_SPAWN_POINTS{ 27 };

        Graph* m_pGraph{};
        Creature m_CreatureType{};
        BlockSurface m_SpawnSurface{};
        float m_ElapsedTime{};
        float m_SpawnInterval{ 5.f };
        int m_Probability{ 100 };

        std::vector<int> m_SpawnBlockIds{ TOP_SPAWN_POINTS };
        std::vector<GameEngine::GameObject*> m_SpawnedCreatures{};

    public:
        void FixedUpdate() override {};
        void Update() override;
        void Render(vec2 const&) const override {};

        void WipeSpawnedCreatures();
        void Init(CreatureSpawnerInfo const& creatureSpawnerInfo);
        void Init(Creature creatureType, float spawnInterval = 5.f, int spawnProbability = 100);
        CreatureSpawner(GameEngine::GameObject* owner);
        ~CreatureSpawner() override = default;
    };
}

#endif