#ifndef BREED_H
#define BREED_H

#include <Map/Block.h>

#include <Engine/Core/GameObject.h>

namespace Game
{
	class Graph;
	class Breed
	{
	public:
        virtual void OnNewBlock(Block* block) = 0;
        virtual void OnEmptyBlock(GameEngine::GameObject& object) = 0;

        virtual ~Breed() = default;
	};

	class QBertBreed final : public Breed
	{
	public:
		void OnNewBlock(Block* block) override;
		void OnEmptyBlock(GameEngine::GameObject& object) override;

        QBertBreed(GameEngine::GameObject* owner);
        ~QBertBreed() override = default;
	};

	class EnemyBreed : public Breed
	{
	public:
		void OnNewBlock(Block*) override {};
		void OnEmptyBlock(GameEngine::GameObject& object) override;
		
        virtual ~EnemyBreed() override = default;
	};
}

#endif