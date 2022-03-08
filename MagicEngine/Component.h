#pragma once

#include "Object.h"

class AActor;

class MComponent :
    public MObject
{
protected:
    AActor* Owner = nullptr;
public:
    const AActor* GetOwner() const { return Owner; }

    void SetOwner(AActor* NewOwner) { Owner = NewOwner; }
};

