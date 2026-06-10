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
        virtual void OnNewBlock(GameEngine::GameObject& object, Block* block) = 0;
        virtual void OnEmptyBlock(GameEngine::GameObject& object) = 0;
        virtual void OnEndOfPath(GameEngine::GameObject& object) = 0;

        virtual ~Breed() = default;
	};

	class QBertBreed final : public Breed
	{
	private:
		int m_Score{};

	public:
		void OnNewBlock(GameEngine::GameObject& object, Block* block) override;
		void OnEmptyBlock(GameEngine::GameObject& object) override;
		void OnEndOfPath(GameEngine::GameObject&) override {};

        QBertBreed(GameEngine::GameObject* owner);
        ~QBertBreed() override = default;
	};

	class EnemyBreed : public Breed
	{
	public:
		virtual void OnNewBlock(GameEngine::GameObject&, Block*) override {};
		virtual void OnEmptyBlock(GameEngine::GameObject& object) override;
		virtual void OnEndOfPath(GameEngine::GameObject&) override {};
		
        virtual ~EnemyBreed() override = default;
	};

	class PurpleSlimeBreed final : public EnemyBreed
	{
	public:
		void OnEndOfPath(GameEngine::GameObject& object) override;

		~PurpleSlimeBreed() override = default;
	};
}

#endif