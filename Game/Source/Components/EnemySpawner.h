#ifndef ENEMY_SPAWNER_H
#define ENEMY_SPAWNER_H

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>

#include <memory>

namespace Game
{
    namespace Spawner
    {
        std::unique_ptr<GameEngine::GameObject> ConstructCoily();
        //inline std::unique_ptr<GameEngine::GameObject> ConstructUgg();
        //inline std::unique_ptr<GameEngine::GameObject> ConstructWrongWay();
    }

    class EnemySpawner final : public GameEngine::BaseComponent
    {
    private:
        float m_ElapsedTime{};
        float m_SpawnInterval{ 5.f };

    public:
    };
}

#endif