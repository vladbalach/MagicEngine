#pragma once

#include "PCH.h"
#include "Actor.h"

class ARock :
    public AActor
{
protected:
    MShapeComponent* ShapeCmp = nullptr;

public:
    virtual void Tick(float DeltaSeconds) override;

    void BeginPlay() override;
};

