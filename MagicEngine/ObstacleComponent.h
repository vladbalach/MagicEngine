#pragma once

#include "SceneComponent.h"

/** Obstacle in world. Used to calculate path finding */
class MObstacleComponent :
    public MSceneComponent
{
protected:
    FVector2D Extension;

    bool bCalculateForPathFinding = false;
public:
    void SetCalculateForPathFinding(bool bNewPathFinding) { bCalculateForPathFinding = bNewPathFinding; }

    bool GetCalculateForPathFinding() const { return bCalculateForPathFinding; }

    FVector2D GetExtension() const { return Extension; }

    void SetExtension(FVector2D NewExtension) { Extension = NewExtension; }
};

