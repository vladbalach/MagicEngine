#include "Actor.h"
#include "ShapeComponent.h"

using Super = MObject;

void AActor::RegisterForInput()
{
	GEngine->RegisterActorForInput(this);
}

void AActor::InputReceived(const std::vector<SDL_Event>& Events)
{
	// implement in derived
}

void AActor::Tick(float DeltaSeconds)
{
}

bool AActor::ShouldDraw()
{
	return bVisible;
}

std::vector<MShapeComponent*> AActor::GetShapeComponents() const
{
	std::vector<MShapeComponent*> ShapeComponents;

	for (MComponent* Cmp : Components)
	{
		MShapeComponent* ShapeCmp = dynamic_cast<MShapeComponent*>(Cmp);
		if (ShapeCmp)
		{
			ShapeComponents.push_back(ShapeCmp);
		}
	}
	return ShapeComponents;
}

void AActor::AddComponent(MComponent* Component)
{
	Component->SetOwner(this);
	Components.push_back(Component);
}

void AActor::BeginPlay()
{

}
