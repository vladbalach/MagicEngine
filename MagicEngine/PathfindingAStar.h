#pragma once

#include "PathfindingAlgorithm.h"



class FPathfindingAStar : public FPathfindingAlgorithm
{
	struct FAStarInfo
	{
		// path to graph node
		float PathLength = 0.f;

		// dist squared to target point
		float HeuristicFunction = 0.f;
	};
protected:


	FGraphNode* StartNode = nullptr;
	FGraphNode* FinishNode = nullptr;

	FGraphNode* CurrentNode = nullptr;

	/** Map with nodes and info about this node */
	std::map< FGraphNode*, FAStarInfo> OpenList;

public:


	std::vector<FGraphNode*> ReconstructPath(std::map<FGraphNode*, FGraphNode*>& CameFrom, FGraphNode* Current);

	EFindPathStatus FindPathIteration();
	virtual EFindPathStatus SearchPath(FGraphNode* StartNode, FGraphNode* FinishNode) override;
};

