#pragma once
#include <Actor.h>

class MCameraComponent;

class APlayerCameraActor :
    public AActor
{
    MCameraComponent* Camera = nullptr;

    FVector2D PrevMousePos;
    bool MouseDown = false;

    void AddMoveRequest(FVector2D Velocity);
public:
    virtual void BeginPlay() override;

    virtual void Tick(float DeltaSeconds) override;

    void SetActiveCamera();

    void SetBackgroundColor(FColor NewBackgroundColor);

	void InputReceived(const std::vector<SDL_Event>& Events) override;

    std::vector<MShapeComponent*> GetShapeComponents() const override;
};

