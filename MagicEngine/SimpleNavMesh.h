#pragma once
#include "Actor.h"
#include "PathfindingAlgorithm.h"

#include "PCH.h"

struct FGraphNode;
class FGraph;

class ASimpleNavMesh : public AActor
{
protected:

	FVector2D Extension{1000.f, 1000.f};

	float TileSize = 50.f;

	FGraph* Graph = nullptr;

	MShapeComponent* ShapeComponent = nullptr;

	std::vector<FGraphNode*> Nodes;

	/** Creates graph from vector of nodes */
	void CreateGraphFromVector(FVector2D TileConunt, std::vector<FGraphNode*>& Nodes);

	FPathfindingAlgorithm* Algorithm = nullptr;

	FVector2D StartPathPoint;
	FVector2D FinishPathPoint;

public:
	void BeginPlay() override;

	void Generate();

	void Regenerate();

	/** Check squared area for pathfinding */
	bool CanMoveInArea(FVector2D Location, FVector2D Extension) const;

	/** Get graph node corresponding to some location */
	FGraphNode* TraceLocationToNavMesh(FVector2D PointLocation);

	virtual std::vector<MShapeComponent*> GetShapeComponents() const override;

	/** Returns points in the world for moving. Empty if no path */
	std::vector<FVector2D> BuildPath(FVector2D StartPoint, FVector2D FinishPoint);

	virtual void InputReceived(const std::vector<SDL_Event>& Events) override;

	virtual EFindPathStatus FindPathBetweenNodes(FGraphNode* StartNode, FGraphNode* FinishNode);

};


