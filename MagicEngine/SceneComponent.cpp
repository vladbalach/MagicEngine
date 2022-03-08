#include "SceneComponent.h"
#include "Actor.h"

FVector2D MSceneComponent::GetWorldLocation() const
{
	if (Owner)
	{
		return Owner->GetLocation() + RelativeLocation;
	}
	return FVector2D{};
}
