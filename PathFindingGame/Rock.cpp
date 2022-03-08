#include "Rock.h"

#include "Rectangle.h"
#include "ShapeComponent.h"

using Super = AActor;

void ARock::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ARock::BeginPlay()
{
	AActor::BeginPlay();

	ShapeCmp = static_cast<MShapeComponent*>(NewObject<MShapeComponent>(GEngine->GetCurrentWorld()));
	ShapeCmp->AddShape(std::make_shared<FRectangle>(FRectangle(FColor{ 0, 0, 255, 255 }, { 100.f, 100.f })));

	AddComponent(ShapeCmp);

	Obstacle = static_cast<MObstacleComponent*>(NewObject<MObstacleComponent>(GEngine->GetCurrentWorld()));
	Obstacle->SetExtension({ 100.f, 100.f });
	Obstacle->SetOwner(this);
}
