#pragma once
#include "PCH.h"
#include "Shape.h"

struct FGraphNode;

struct FGraphConnection
{
	int32 Id = -1;
	float Weight = 1.f;
	FGraphNode* Node1 = nullptr;
	FGraphNode* Node2 = nullptr;
};

struct FGraphNode
{
	int32 Id = 0;
	std::vector<FGraphConnection> Connections;

	/** Debug shape for this node */
	std::shared_ptr<FShape> Shape;

	/** For some algorithms world node location is needed */
	FVector2D WorldLocation;
};

/** Graph structure */
class FGraph
{
public:
	virtual ~FGraph() = default;

	std::vector<FGraphNode*> Nodes;

	
};
