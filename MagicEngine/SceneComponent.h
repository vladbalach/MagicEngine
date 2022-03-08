#pragma once

#include "Component.h"

/** Component that has relative location */
class MSceneComponent :
    public MComponent
{
protected:
    FVector2D RelativeLocation;

public:
    void SetRelativeLocation(FVector2D NewRelativeLocation) { RelativeLocation = NewRelativeLocation; }

    FVector2D GetWorldLocation() const;
};

