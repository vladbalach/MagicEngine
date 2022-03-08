#include "Character.h"

#include "Rectangle.h"
#include "ShapeComponent.h"

using Super = AActor;

void ACharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ACharacter::BeginPlay()
{
	AActor::BeginPlay();

	ShapeCmp = static_cast<MShapeComponent*>(NewObject<MShapeComponent>(GEngine->GetCurrentWorld()));
	ShapeCmp->AddShape(std::make_shared<FRectangle>(FRectangle(FColor{ 255, 0, 255, 255 }, { 20.f, 20.f })));

	AddComponent(ShapeCmp);

}
