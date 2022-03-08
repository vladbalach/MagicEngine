#pragma once

#include "PCH.h"
#include "SceneComponent.h"

class MWorld;
class AActor;

class MCameraComponent : public MSceneComponent
{
	std::vector<AActor*> ActorsToDraw;

	FColor BackgroundColor;

public:
	void Render(SDL_Renderer* Renderer);

	void Clipping();

	void SetActive();

	void SetBackgroundColor(FColor Color);

};

