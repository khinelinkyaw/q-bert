#ifndef BREED_H
#define BREED_H

#include <Map/Block.h>
#include <Misc/Structs.h>
#include <Misc/Enums.h>

#include <Engine/Core/GameObject.h>

namespace Game
{
	enum class Weakness
	{
		None,
		NormalEnemy,
		Qbert,
    };

	class Graph;
	class Breed
	{
	protected:
		CreatureInfo m_CreatureInfo{};
        Weakness m_Weakness{ Weakness::None };

		void DecreaseLive(GameEngine::GameObject& object);
		void IncreaseScore(int increment, GameEngine::GameObject& object);

	public:
        virtual void OnNewBlock(GameEngine::GameObject& object, Block* block) = 0;
        virtual void OnEmptyBlock(GameEngine::GameObject& object);
		virtual void OnCollision(GameEngine::GameObject& object, Weakness attacker) = 0;
        virtual void OnEndOfPath(GameEngine::GameObject& object) = 0;

        Weakness GetWeakness() const { return m_Weakness; }
		void SetPlayerIndex(PlayerIndex playerIndex) { m_CreatureInfo.PlayerIndex = playerIndex; }
		Breed(Weakness weakness) : m_Weakness{ weakness } {};
        virtual ~Breed() = default;
	};

	class QBertBreed final : public Breed
	{
	public:
		void OnNewBlock(GameEngine::GameObject& object, Block* block) override;
		void OnEmptyBlock(GameEngine::GameObject& object) override;
		void OnCollision(GameEngine::GameObject& object, Weakness attacker) override;
		void OnEndOfPath(GameEngine::GameObject&) override {};

        QBertBreed(GameEngine::GameObject* owner);
        ~QBertBreed() override = default;
	};

	class EnemyBreed : public Breed
	{
	public:
		virtual void OnNewBlock(GameEngine::GameObject&, Block*) override {};
		virtual void OnCollision(GameEngine::GameObject&, Weakness) override {};
		virtual void OnEndOfPath(GameEngine::GameObject&) override {};
		
		EnemyBreed() : Breed{ Weakness::None } {};
        virtual ~EnemyBreed() override = default;
	};

	class PurpleSlimeBreed final : public EnemyBreed
	{
	public:
		void OnEndOfPath(GameEngine::GameObject& object) override;

		~PurpleSlimeBreed() override = default;
	};

	class GreenEnemyBreed final : public EnemyBreed
	{
	public:
        virtual void OnCollision(GameEngine::GameObject& object, Weakness attacker) override;
		virtual void OnNewBlock(GameEngine::GameObject&, Block* block) override;

		GreenEnemyBreed() : EnemyBreed() { m_Weakness = Weakness::Qbert; }
        ~GreenEnemyBreed() override = default;
	};
}

#endif
