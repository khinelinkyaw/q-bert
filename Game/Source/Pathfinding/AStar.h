#ifndef ASTAR_H
#define ASTAR_H

#include <Map/Block.h>
#include <Map/Graph.h>
#include <Map/Connection.h>
#include <Pathfinding/Heuristics.h>

#include <vector>

// This implementation is my own implementation from Game AI course
namespace Game
{
	class AStar final
	{
	public:
		struct PathResult
		{
			float totalCost = 0.f;
			bool pathFound = true;
		};

		struct BlockRecord
		{
			Block const* pBlock = nullptr;
			Connection const* pConnection = nullptr;
			float costSoFar = 0.f; // accumulated g-costs of all the connections leading up to this one
			float distanceToDest = 0.f; // h-cost
			float estimatedTotalCost = 0.f; // f-cost (= costSoFar + h-cost)

			void CalculateEstimatedTotalCost()
			{
				estimatedTotalCost = costSoFar + distanceToDest;
			}

			bool operator==(const BlockRecord& other) const
			{
				return pBlock == other.pBlock
					&& pConnection == other.pConnection
					&& costSoFar == other.costSoFar
					&& estimatedTotalCost == other.estimatedTotalCost;
			};

			bool operator<(const BlockRecord& other) const
			{
				return estimatedTotalCost < other.estimatedTotalCost;
			};
		};

	private:
		static inline HeuristicFunctions::Heuristic m_HeuristicFunction{ HeuristicFunctions::Manhattan };

		static inline void BacktrackFullPath(std::vector<BlockRecord> const& ClosedList, BlockRecord const& startingBlockRecord, std::vector<Block const*>& finalPath);

	public:
		static inline float GetHeuristicCost(Block const& startBlock, Block const& endBlock);
		//static std::vector<vec3> ConvertToFloatPath(std::vector<Block*> const& blockPath, Graph* pGraph);
		static PathResult FindPath(Block* const pStartBlock, Block * const pDestBlock, Graph* pGraph, std::vector<Block const*>* finalPath);
	};
}

#endif