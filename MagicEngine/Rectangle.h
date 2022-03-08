#pragma once
#include "PCH.h"
#include "Shape.h"

class FRectangle :
    public FShape
{
    FColor Color;

    FVector2D Extends;

    FVector2D DrawLocationShift;

public:

    FRectangle();

    FRectangle(FColor Color, FVector2D Extends);

    FRectangle(FColor Color, FVector2D Extends, FVector2D DrawLocationShift);

    void Render(SDL_Renderer* Renderer, FVector2D OnScreenLocation, float Zoom) const override;

    void SetColor(FColor NewColor) { Color = NewColor; }

    void SetExtends(FVector2D NewExtends) { Extends = NewExtends; }
};

