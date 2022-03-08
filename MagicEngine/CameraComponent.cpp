#include "CameraComponent.h"
#include "World.h"
#include "Actor.h"
#include "CameraManager.h"
#include "ShapeComponent.h"

void MCameraComponent::Render(SDL_Renderer* Renderer)
{
	Clipping();
	
	SDL_SetRenderDrawColor(Renderer, BackgroundColor.R, BackgroundColor.G, BackgroundColor.B, BackgroundColor.A);
	SDL_RenderClear(Renderer);

	for (auto It = ActorsToDraw.begin(); It != ActorsToDraw.end(); ++It)
	{
		AActor* Actor = *It;
		if (Actor)
		{
			std::vector<MShapeComponent*> Shapes = (Actor)->GetShapeComponents();

			for (MShapeComponent* ShapeComponent : Shapes)
			{
				if (ShapeComponent)
				{
					ShapeComponent->Render(Renderer, Actor->GetLocation() - GetWorldLocation(), 1.f);
				}
			}
		}
	}

	SDL_RenderPresent(Renderer);
}

void MCameraComponent::Clipping()
{
	// TODO clipping. Remove actors from render that not on screen
	if (World)
	{
		ActorsToDraw = World->GetAllActors();
	}
}

void MCameraComponent::SetActive()
{
	MCameraManager::SetActiveCamera(this);
}

void MCameraComponent::SetBackgroundColor(FColor Color)
{
	BackgroundColor = Color;
}
