#pragma once

#include "PCH.h"

class FGraph;
class FGraphNode;

enum class EFindPathStatus
{
	InProgress,
	NoPath,
	PathFound
};

struct FPathfindingData
{
	FVector2D StartPathPoint;
	FVector2D FinishPathPoint;
};

class FPathfindingAlgorithm
{
protected:
	FGraph* Graph = nullptr;

	/** Some algorithms needs this data (AStar, for example) */
	FVector2D StartPathPoint;
	FVector2D FinishPathPoint;

	std::vector<FGraphNode*> TotalPath;

public:
	virtual void SetData(const FPathfindingData& Data);

	virtual std::vector<FGraphNode*> GetTotalPath() const { return TotalPath; }

	virtual EFindPathStatus SearchPath(FGraphNode* StartNode, FGraphNode* FinishNode);
};

