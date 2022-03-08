#include "PlayerCameraActor.h"
#include "CameraComponent.h"

void APlayerCameraActor::AddMoveRequest(FVector2D Velocity)
{
	SetLocation(GetLocation() + Velocity);
}

void APlayerCameraActor::BeginPlay()
{
	AActor::BeginPlay();

	Camera = static_cast<MCameraComponent*>(NewObject<MCameraComponent>(GetWorld()));
	Camera->SetOwner(this);
}

void APlayerCameraActor::Tick(float DeltaSeconds)
{
	AActor::Tick(DeltaSeconds);
}

void APlayerCameraActor::SetActiveCamera()
{
	Camera->SetActive();
}

void APlayerCameraActor::SetBackgroundColor(FColor NewBackgroundColor)
{
	Camera->SetBackgroundColor(NewBackgroundColor);
}

void APlayerCameraActor::InputReceived(const std::vector<SDL_Event>& Events)
{
	AActor::InputReceived(Events);

	for (const SDL_Event& Event : Events)
	{
		if (Event.type == SDL_MOUSEBUTTONDOWN) {
			PrevMousePos = { (float)Event.motion.x, (float)Event.motion.y };
			if (Event.button.button == SDL_BUTTON_LEFT) {
				MouseDown = true;
			}
		}
		if (Event.type == SDL_MOUSEMOTION) {
			float X = Event.motion.x;
			float Y = Event.motion.y;
			FVector2D CurrentMousePos = { X, Y };
			if (MouseDown) {
				AddMoveRequest(PrevMousePos - CurrentMousePos);
			}
			PrevMousePos = CurrentMousePos;
		}
		if (Event.type == SDL_MOUSEBUTTONUP) {
			MouseDown = false;
		}
	}
}

std::vector<MShapeComponent*> APlayerCameraActor::GetShapeComponents() const
{
	// do nothing. We do not render this actor, so don't need to check for components
	return std::vector<MShapeComponent*>{};
}
