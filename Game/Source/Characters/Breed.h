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
        virtual void OnEmptyBlock(GameEngine::GameObject& object, Graph const& graph) = 0;
        virtual ~Breed() = default;
	};

	class QBertBreed final : public Breed
	{
	public:
		void OnNewBlock(Block* block) override;
		void OnEmptyBlock(GameEngine::GameObject& object, Graph const& graph) override;

        ~QBertBreed() override = default;
	};

	class SlimeBreed : public Breed
	{
	public:
		void OnNewBlock(Block*) override {};
		void OnEmptyBlock(GameEngine::GameObject& object, Graph const& graph) override;
		
		virtual void OnPathEnd() = 0;

        virtual ~SlimeBreed() override = default;
	};

	class RedSlimeBreed final : public SlimeBreed
	{
	public:
		void OnPathEnd() override {};

        ~RedSlimeBreed() override = default;
	};

	class PurpleSlimeBreed final : public SlimeBreed
	{
	public:
        void OnPathEnd() override {};

        ~PurpleSlimeBreed() override = default;
	};
}

#endif