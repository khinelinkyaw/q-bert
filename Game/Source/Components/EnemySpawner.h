#ifndef ENEMY_SPAWNER_H
#define ENEMY_SPAWNER_H

#include <Components/BaseCreature.h>

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Misc/Enums.h>

#include <vector>

namespace Game
{
    namespace Builder
    {
        void AddCommonComponents(GameEngine::GameObject& gameObject, GameEngine::Pivot pivot = GameEngine::Pivot::MiddleDown);
        void InitQBertComponents(GameEngine::GameObject& gameObject);
        void InitCoilyComponents(GameEngine::GameObject& gameObject);
        void InitSlimeComponents(GameEngine::GameObject& gameObject, Creature creatureType);

        GameEngine::GameObject& BuildQBert();
        GameEngine::GameObject& BuildCoily();
        GameEngine::GameObject& BuildPurpleSlime();
        GameEngine::GameObject& BuildGreenSlime();
        GameEngine::GameObject& BuildRedSlime();
        GameEngine::GameObject& BuildUgg();
        GameEngine::GameObject& BuildWrongWay();
    }


    class Graph;
    class CreatureSpawner final : public GameEngine::BaseComponent
    {
    private:
        Graph* m_pGraph{};
        float m_ElapsedTime{};
        float m_SpawnInterval{ 5.f };
        std::vector<int> m_SpawnBlockIds{};

    public:
        GameEngine::GameObject& ConstructCoily(int graphBlockId);
        GameEngine::GameObject& ConstructPurpleSlime(int graphBlockId);
        GameEngine::GameObject& ConstructGreenSlime(int graphBlockId);
        GameEngine::GameObject& ConstructRedSlime(int graphBlockId);

        CreatureSpawner(GameEngine::GameObject* owner);
        ~CreatureSpawner() override = default;
    };
}

#endif