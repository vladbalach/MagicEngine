#include "PathfindingAStar.h"

#include "Graph.h"
#include "Logging.h"


std::vector<FGraphNode*> FPathfindingAStar::ReconstructPath(std::map<FGraphNode*, FGraphNode*>& CameFrom, FGraphNode* Current)
{
	std::vector<FGraphNode*> TotalPath{Current};
	while (CameFrom.count(Current) != 0)
	{
		Current = CameFrom[Current];
		TotalPath.push_back(Current);
	}
	return TotalPath;
}

EFindPathStatus FPathfindingAStar::FindPathIteration()
{
	if (!CurrentNode)
	{
		CurrentNode = StartNode;
	}

	std::set<FGraphNode*> OpenSet;
	OpenSet.insert(StartNode);

	std::map<FGraphNode*, FGraphNode*> CameFrom;

	std::map<FGraphNode*, float> gScore;
	gScore.insert(std::pair< FGraphNode*, float>{StartNode, 0.f});

	std::map<FGraphNode*, float> fScore;
	fScore.insert(std::pair< FGraphNode*, float>{StartNode, FVector2D::Dist(StartNode->WorldLocation, FinishPathPoint)});

	while (!OpenSet.empty())
	{
		FGraphNode* CurrentNode = nullptr;
		float MinFScore = 9999999.f;
		for (const std::pair< FGraphNode*, float>& Pair : fScore)
		{
			if (Pair.second < MinFScore && OpenSet.count(Pair.first) != 0)
			{
				CurrentNode = Pair.first;
				MinFScore = Pair.second;
			}
		}

		if (CurrentNode == FinishNode)
		{
			TotalPath = ReconstructPath(CameFrom, CurrentNode);
			return EFindPathStatus::PathFound;
		}

		OpenSet.erase(CurrentNode);

		// for each neighbor of CurrentNode
		for (FGraphConnection& Connection : CurrentNode->Connections)
		{
			FGraphNode* NeighborNode = Connection.Node1 != CurrentNode ? Connection.Node1 : Connection.Node2;

			if (NeighborNode)
			{
				float Tentative_gScore = MinFScore + FVector2D::Dist(CurrentNode->WorldLocation, NeighborNode->WorldLocation);

				if (gScore.count(NeighborNode) == 0)
				{
					gScore.insert(std::pair< FGraphNode*, float>{NeighborNode, 999999.f});
				}

				if (Tentative_gScore < gScore[NeighborNode])
				{
					if (CameFrom.count(NeighborNode) == 0)
					{
						CameFrom.insert(std::pair< FGraphNode*, FGraphNode*>{NeighborNode, CurrentNode});
					}

					
					gScore[NeighborNode] = Tentative_gScore;

					if (fScore.count(NeighborNode) == 0)
					{
						fScore.insert(std::pair< FGraphNode*, float>{NeighborNode, 999999.f});
					}

					fScore[NeighborNode] = Tentative_gScore + FVector2D::Dist(NeighborNode->WorldLocation, FinishPathPoint);

					if (OpenSet.count(NeighborNode) == 0)
					{
						OpenSet.insert(NeighborNode);
					}
				}
			}
		}

	}

	return EFindPathStatus::NoPath;

	/*OpenList.insert(std::pair< FGraphNode*, FAStarInfo>{StartNode, AStarInfo});

	AddOpenListDataFromNode(CurrentNode);*/


	//CountFxForEachNode();
	//ChooseBestVariant();
	//FVector2D CurrentNodeCenter;
	//// heuristic function
	//float Hx = FVector2D::DistSqr(CurrentNodeCenter, FinishPathPoint);
	//// distance from start to current point
	//float Gx = ;
	//float Fx = Hx + Gx;
	//return EFindPathStatus::InProgress;
}

EFindPathStatus FPathfindingAStar::SearchPath(FGraphNode* StartNode_, FGraphNode* FinishNode_)
{
	StartNode = StartNode_;
	FinishNode = FinishNode_;
	return FindPathIteration();
}
