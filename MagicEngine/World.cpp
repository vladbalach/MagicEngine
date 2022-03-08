#include "World.h"
#include "Actor.h"

void MWorld::Tick(float DeltaSeconds)
{
	for (auto it = RegisteredActors.begin(); it != RegisteredActors.end(); ++it)
	{
		if (*it)
		{
			(*it)->Tick(DeltaSeconds);
		}
	}
}

void MWorld::RegisterActorForTick(AActor* Actor)
{
	if (std::find(RegisteredActors.begin(), RegisteredActors.end(), Actor) == RegisteredActors.end())
	{
		RegisteredActors.push_back(Actor);
	}
}
