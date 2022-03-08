#pragma once

#include "PCH.h"

class AActor;

class MWorld
{
	std::vector<AActor*> RegisteredActors;

public:
	void Tick(float DeltaSeconds);

	void RegisterActorForTick(AActor* Actor);

	const std::vector<AActor*>& GetAllActors() const { return RegisteredActors; }

};

