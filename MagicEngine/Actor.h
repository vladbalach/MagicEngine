#pragma once

#include "Engine.h"
#include "Object.h"
#include "ObstacleComponent.h"
#include "PCH.h"

class MComponent;
class MShapeComponent;
class FShape;

class AActor : public MObject
{
protected:
	FVector2D Location;

	bool bVisible = true;

	std::vector<MComponent*> Components;

	/** Collision object */
	MObstacleComponent* Obstacle = nullptr;
public:

	/** Register this actor to receive input from devices (keyboard, mouse, sensor, etc.) */
	void RegisterForInput();

	/** Called when input received */
	virtual void InputReceived(const std::vector<SDL_Event>& Events);

	virtual void Tick(float DeltaSeconds);

	/** Indicates whether the engine need to draw this actor */
	virtual bool ShouldDraw();

	/** This function calls for render. Default implementation returns all shape components of this actor. */
	virtual std::vector<MShapeComponent*> GetShapeComponents() const;

	void AddComponent(MComponent* Component);

	FVector2D GetLocation() const { return Location; }

	void SetLocation(FVector2D NewLocation) { Location = NewLocation; }

	const MObstacleComponent* GetObstacle() const { return Obstacle; }

	virtual void BeginPlay();
};

template<typename ActorClass>
AActor* SpawnActor(MWorld* World)
{
	AActor* NewActor = new ActorClass();

	GEngine->RegisterActorForTick(NewActor);

	NewActor->SetWorld(World);
	NewActor->BeginPlay();

	return NewActor;
}

template<typename ActorClass>
AActor* SpawnActor(MWorld* World, FVector2D Location)
{
	AActor* NewActor = new ActorClass();

	GEngine->RegisterActorForTick(NewActor);

	NewActor->SetWorld(World);
	NewActor->SetLocation(Location);
	NewActor->BeginPlay();

	return NewActor;
}

