#include "SimpleNavMesh.h"
#include "Box.h"
#include "CameraComponent.h"
#include "CameraManager.h"
#include "Graph.h"
#include "Logging.h"
#include "PathfindingAStar.h"
#include "Rectangle.h"
#include "ShapeComponent.h"

void ASimpleNavMesh::CreateGraphFromVector(FVector2D TileConunt, std::vector<FGraphNode*>& Nodes)
{
	for (int32 i = 0; i < TileConunt.X; i++)
	{
		for (int32 j = 0; j < TileConunt.Y; j++)
		{
			const int32 TileCountY = static_cast<int32>(TileConunt.Y);
			FGraphNode* Node = Nodes[i * TileCountY + j];
			if (Node)
			{
				// check left
				if (i > 0 && Nodes[( i - 1) * TileCountY + j])
				{
					FGraphConnection Connection;
					Connection.Weight = TileSize;
					Connection.Node1 = Node;
					Connection.Node2 = Nodes[(i - 1) * TileCountY + j];
					Node->Connections.push_back(Connection);
				}
				// check right
				if (i < (TileConunt.X - 1) && Nodes[(i + 1) * TileCountY + j])
				{
					FGraphConnection Connection;
					Connection.Weight = TileSize;
					Connection.Node1 = Node;
					Connection.Node2 = Nodes[(i + 1) * TileCountY + j];
					Node->Connections.push_back(Connection);
				}

				// check above
				if (j > 0 && Nodes[i * TileCountY + j - 1])
				{
					FGraphConnection Connection;
					Connection.Weight = TileSize;
					Connection.Node1 = Node;
					Connection.Node2 = Nodes[i * TileCountY + j - 1];
					Node->Connections.push_back(Connection);
				}

				// check under
				if (j < (TileCountY - 1) && Nodes[i * TileCountY + j + 1])
				{
					FGraphConnection Connection;
					Connection.Weight = TileSize;
					Connection.Node1 = Node;
					Connection.Node2 = Nodes[i * TileCountY + j + 1];
					Node->Connections.push_back(Connection);
				}
			}

			Graph->Nodes.push_back(Node);
		}
	}
}

void ASimpleNavMesh::BeginPlay()
{
	AActor::BeginPlay();

	Graph = new FGraph();

	ShapeComponent = static_cast<MShapeComponent*>(NewObject<MShapeComponent>(GEngine->GetCurrentWorld()));
	

	AddComponent(ShapeComponent);

	Algorithm = new FPathfindingAStar();
	Generate();
}

void ASimpleNavMesh::Generate()
{
	Nodes.clear();
	FVector2D TilesCount = Extension / TileSize;

	TilesCount = { ceil(TilesCount.X), ceil(TilesCount.Y) };
	Extension = TilesCount * TileSize;

	for (int32 i = 0; i < TilesCount.X; i++)
	{
		for (int32 j = 0; j < TilesCount.Y; j++)
		{
			Nodes.push_back(nullptr);
			if (CanMoveInArea(Location + FVector2D{ i * TileSize, j * TileSize }, FVector2D{ TileSize, TileSize }))
			{
				FVector2D Extends = { TileSize - 2, TileSize - 2 };
				FVector2D DrawLocationShift = { i * TileSize + 1, j * TileSize + 1 };
				std::shared_ptr<FRectangle> Rect = std::make_shared<FRectangle>(FRectangle(FColor{ 0, 255, 0, 120 }, Extends, DrawLocationShift));
				FGraphNode* NewGraphNode = new FGraphNode();
				NewGraphNode->WorldLocation = DrawLocationShift + GetLocation() + (Extends / 2);
				Nodes[i * TilesCount.Y + j] = NewGraphNode;
				NewGraphNode->Shape = Rect;
				ShapeComponent->AddShape(NewGraphNode->Shape);
			}
		}
	}

	CreateGraphFromVector(TilesCount, Nodes);
}

void ASimpleNavMesh::Regenerate()
{
	if (ShapeComponent)
	{
		ShapeComponent->ClearShapes();
	}
	Generate();
}

bool ASimpleNavMesh::CanMoveInArea(FVector2D Location, FVector2D Extension) const
{
	FBox CheckBox{ Location, Location + Extension };
	for (AActor* Actor : World->GetAllActors())
	{
		if (Actor)
		{
			const MObstacleComponent* Obstacle = Actor->GetObstacle();
			if (Obstacle)
			{
				FVector2D ObstacleLocation = Obstacle->GetWorldLocation();
				FVector2D ObstacleExtension = Obstacle->GetExtension();

				FBox ObstacleBox{ ObstacleLocation , ObstacleLocation  + ObstacleExtension};
				if (ObstacleBox.IsIntersects(CheckBox))
				{
					return false;
				}
			}
		}
	}
	return true;
}

FGraphNode* ASimpleNavMesh::TraceLocationToNavMesh(FVector2D PointLocation)
{
	if (!PointLocation.IsInBoundsHard(Location, Location + Extension))
	{
		return nullptr;
	}

	FVector2D Tile = (PointLocation - Location) / TileSize;
	Tile = { floor(Tile.X), floor(Tile.Y) };

	FVector2D TilesCount = Extension / TileSize;

	TilesCount = { ceil(TilesCount.X), ceil(TilesCount.Y) };

	if (Nodes[Tile.X * TilesCount.Y + Tile.Y])
	{
		return Nodes[Tile.X * TilesCount.Y + Tile.Y];
	}
	return nullptr;
}

std::vector<MShapeComponent*> ASimpleNavMesh::GetShapeComponents() const
{
	return { ShapeComponent };
}

std::vector<FVector2D> ASimpleNavMesh::BuildPath(FVector2D StartPoint, FVector2D FinishPoint)
{
	FGraphNode* StartNode = TraceLocationToNavMesh(StartPoint);
	FGraphNode* FinishNode = TraceLocationToNavMesh(FinishPoint);

	if (StartNode && FinishNode)
	{
		StartPathPoint = StartPoint;
		FinishPathPoint = FinishPoint;
		FRectangle* RectangleStart = dynamic_cast<FRectangle*>(StartNode->Shape.get());
		if (RectangleStart)
		{
			RectangleStart->SetColor(FColor{ 0, 255, 255, 255 });
		}

		FRectangle* RectangleFinish = dynamic_cast<FRectangle*>(FinishNode->Shape.get());
		if (RectangleFinish)
		{
			RectangleFinish->SetColor(FColor{ 255, 0, 255, 255 });
		}

		FindPathBetweenNodes(StartNode, FinishNode);
		// Build path between nodes
	}

	if (!StartNode)
	{
		LOG("Start point not in current NavMesh")
	}

	if (!FinishNode)
	{
		LOG("Finish point not in current NavMesh")
	}
	return std::vector<FVector2D>{};
}

void ASimpleNavMesh::InputReceived(const std::vector<SDL_Event>& Events)
{
	AActor::InputReceived(Events);

	/*MCameraComponent* ActiveCamera = MCameraManager::GetActiveCamera();
	if (ActiveCamera)
	{
		for (const SDL_Event& Event : Events)
		{
			if (Event.type == SDL_MOUSEBUTTONDOWN) {
				float X = Event.motion.x;
				float Y = Event.motion.y;
				FVector2D ScreenMousePos = { X, Y };
				FVector2D CameraLocation = ActiveCamera->GetWorldLocation();
				FVector2D WorldClickPos = CameraLocation + ScreenMousePos;
				FGraphNode* Node = TraceLocationToNavMesh(WorldClickPos);
				if (Node)
				{
					FRectangle* Rectangle = dynamic_cast<FRectangle*>(Node->Shape.get());
					if (Rectangle)
					{
						Rectangle->SetColor(FColor{ 255, 0, 0, 255 });
					}

					for (FGraphConnection& Connection : Node->Connections)
					{
						if (Connection.Node1 && Connection.Node1 != Node)
						{
							FRectangle* RectangleNode = dynamic_cast<FRectangle*>(Connection.Node1->Shape.get());
							if (RectangleNode)
							{
								RectangleNode->SetColor(FColor{ 255, 255, 0, 255 });
							}
						}

						if (Connection.Node2 && Connection.Node2 != Node)
						{
							FRectangle* RectangleNode = dynamic_cast<FRectangle*>(Connection.Node2->Shape.get());
							if (RectangleNode)
							{
								RectangleNode->SetColor(FColor{ 255, 255, 0, 255 });
							}
						}
					}
				}
			}
		}
	}*/
}

EFindPathStatus ASimpleNavMesh::FindPathBetweenNodes(FGraphNode* StartNode, FGraphNode* FinishNode)
{
	if (StartNode && FinishNode
		&& std::count(Nodes.begin(), Nodes.end(), StartNode) > 0
		&& std::count(Nodes.begin(), Nodes.end(), FinishNode) > 0)
	{
		if (Algorithm)
		{
			Algorithm->SetData(FPathfindingData{ StartPathPoint, FinishPathPoint });
			if (Algorithm->SearchPath(StartNode, FinishNode) == EFindPathStatus::PathFound)
			{
				LOG("Path found")
				std::vector<FGraphNode*> TotalPath = Algorithm->GetTotalPath();
				for (FGraphNode* Node : TotalPath)
				{
					FRectangle* RectangleFinish = dynamic_cast<FRectangle*>(Node->Shape.get());
					if (RectangleFinish)
					{
						RectangleFinish->SetColor(FColor{ 255, 0, 0, 255 });
					}
				}
			}
			else
			{
				LOG("Path not found")
			}
		}
	}
	return EFindPathStatus::NoPath;
}
