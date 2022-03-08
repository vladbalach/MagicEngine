#pragma once

#include "PCH.h"

/**
 * Abstract base shape class.
 * Images, brushes, colored figures and so on. All what can be rendered
 */
class FShape
{
public:
	virtual void Render(SDL_Renderer* Renderer, FVector2D OnScreenLocation, float Zoom) const = 0;

};
