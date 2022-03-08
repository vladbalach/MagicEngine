#include "Rectangle.h"

FRectangle::FRectangle()
{
}

FRectangle::FRectangle(FColor Color_, FVector2D Extends_)
	: Color(Color_),
	Extends(Extends_)
{
}

FRectangle::FRectangle(FColor Color_, FVector2D Extends_, FVector2D DrawLocationShift_)
    : Color(Color_),
    Extends(Extends_),
	DrawLocationShift(DrawLocationShift_)
{

}

void FRectangle::Render(SDL_Renderer* Renderer, FVector2D OnScreenLocation, float Zoom) const
{
    SDL_Rect r;
    r.x = OnScreenLocation.X + DrawLocationShift.X;
    r.y = OnScreenLocation.Y + DrawLocationShift.Y;
    r.w = Extends.X;
    r.h = Extends.Y;

    SDL_SetRenderDrawColor(Renderer, Color.R, Color.G, Color.B, Color.A);
    SDL_RenderFillRect(Renderer, &r);
}
