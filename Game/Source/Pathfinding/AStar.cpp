#include <Pathfinding/AStar.h>

#include <algorithm>
#include <cstdlib>
#include <vector>

using namespace Game;

void AStar::BacktrackFullPath(std::vector<BlockRecord> const& ClosedList, BlockRecord const& startingBlockRecord, std::vector<Block const*>& finalPath)
{
	BlockRecord currentBlockRecord{ startingBlockRecord };

	while (currentBlockRecord.pConnection != nullptr)
	{
		finalPath.push_back(currentBlockRecord.pBlock);

		auto NextNodeIter = std::ranges::find_if(ClosedList, [&currentBlockRecord](BlockRecord const& Record)
			{
				return currentBlockRecord.pConnection->GetFromBlock() == Record.pBlock->GetId();
			});

		currentBlockRecord = *NextNodeIter;
	}

	finalPath.push_back(currentBlockRecord.pBlock);
	std::ranges::reverse(finalPath);
}

float AStar::GetHeuristicCost(Block const& startBlock, Block const& endBlock)
{
	auto toDest{ startBlock.GetPosition() - endBlock.GetPosition() };

	return m_HeuristicFunction(std::abs(toDest.x), std::abs(toDest.y));
}


AStar::PathResult AStar::FindPath(Block* const pStartBlock, Block* const pDestBlock, Graph* pGraph, std::vector<Block const*>* finalPath)
{
	PathResult result{};
	std::vector<BlockRecord> OpenList{};
	std::vector<BlockRecord> ClosedList{};

	BlockRecord CurrentBlockRecord{};
	CurrentBlockRecord.pBlock = pStartBlock;
	CurrentBlockRecord.pConnection = nullptr;
	CurrentBlockRecord.costSoFar = 0.0f;
	CurrentBlockRecord.distanceToDest = GetHeuristicCost(*pStartBlock, *pDestBlock);
	CurrentBlockRecord.CalculateEstimatedTotalCost();
	OpenList.push_back(CurrentBlockRecord);

	BlockRecord NeighborBlockRecord{};
	auto FindNeighborNodeId{ [&NeighborBlockRecord](BlockRecord const& InnerRecord)
	{
		return	InnerRecord.pBlock->GetId() == NeighborBlockRecord.pBlock->GetId();
	} };

	while (!OpenList.empty())
	{
		auto NodeRecordIter = std::min_element(OpenList.begin(), OpenList.end());
		CurrentBlockRecord = *NodeRecordIter;
		auto CurrentNodeId{ CurrentBlockRecord.pBlock->GetId() };

		if (CurrentBlockRecord.pBlock == pDestBlock)
		{
			ClosedList.push_back(CurrentBlockRecord);
			OpenList.clear();
			result.totalCost = CurrentBlockRecord.estimatedTotalCost;
			break;
		}

		auto Connections = pGraph->GetConnectionsFromCell(CurrentNodeId);

		for (auto Conn : Connections)
		{
			NeighborBlockRecord.pBlock = pGraph->GetBlock(Conn->GetToBlock());
			NeighborBlockRecord.pConnection = Conn;
			NeighborBlockRecord.costSoFar = CurrentBlockRecord.costSoFar + Conn->GetWeight();
			NeighborBlockRecord.distanceToDest = GetHeuristicCost(*(NeighborBlockRecord.pBlock), *pDestBlock);
			NeighborBlockRecord.CalculateEstimatedTotalCost();

			auto OpenListIter = std::ranges::find_if(OpenList, FindNeighborNodeId);
			auto ClosedListIter = std::ranges::find_if(ClosedList, FindNeighborNodeId);

			if (OpenListIter != OpenList.end() and NeighborBlockRecord.costSoFar < OpenListIter->costSoFar)
			{
				OpenList.erase(OpenListIter);
			}
			else if (ClosedListIter != ClosedList.end() and NeighborBlockRecord.costSoFar < ClosedListIter->costSoFar)
			{
				ClosedList.erase(ClosedListIter);
			}
			else if (OpenListIter != OpenList.end() or ClosedListIter != ClosedList.end())
			{
				continue;
			}

			OpenList.push_back(NeighborBlockRecord);
		}

		ClosedList.push_back(CurrentBlockRecord);
		std::erase(OpenList, CurrentBlockRecord);
	}

	auto GoalNodeIter = std::ranges::find_if(ClosedList, [&pDestBlock](BlockRecord const& InnerRecord)
		{
			return InnerRecord.pBlock->GetId() == pDestBlock->GetId();
		});

	if (GoalNodeIter == ClosedList.end())
	{
		auto ClosestNodeIter{ std::ranges::min_element(ClosedList, [](BlockRecord const& RecordA, BlockRecord const& RecordB)
		{
			return RecordA.distanceToDest < RecordB.distanceToDest;
		}) };

		CurrentBlockRecord = *ClosestNodeIter;
		result.pathFound = false;
	}

	if (finalPath != nullptr)
	{
		BacktrackFullPath(ClosedList, CurrentBlockRecord, *finalPath);
	}

	return result;
}
