#pragma once

#include "PCH.h"
#include "Actor.h"

class ACharacter :
    public AActor
{
protected:
    MShapeComponent* ShapeCmp = nullptr;

public:
    virtual void Tick(float DeltaSeconds) override;

    void BeginPlay() override;
};

