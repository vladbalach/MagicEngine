#include "ShapeComponent.h"
#include "Shape.h"

void MShapeComponent::Render(SDL_Renderer* Renderer, FVector2D OnScreenLocation, float Zoom) const
{
	for (const std::shared_ptr<FShape>& Shape : Shapes)
	{
		if (Shape)
		{
			Shape->Render(Renderer, OnScreenLocation, Zoom);
		}
	}
}

void MShapeComponent::ClearShapes()
{
	Shapes.clear();
}

