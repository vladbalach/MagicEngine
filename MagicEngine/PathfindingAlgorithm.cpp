#include "PathfindingAlgorithm.h"
#include "Graph.h"

void FPathfindingAlgorithm::SetData(const FPathfindingData& Data)
{
	StartPathPoint = Data.StartPathPoint;
	FinishPathPoint = Data.FinishPathPoint;
}

EFindPathStatus FPathfindingAlgorithm::SearchPath(FGraphNode* StartNode, FGraphNode* FinishNode)
{
	return EFindPathStatus::NoPath;
}
