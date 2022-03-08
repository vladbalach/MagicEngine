#pragma once

#include "PCH.h"
#include "SceneComponent.h"

class FShape;

/** Shape component.
 * Used to draw any shape
 */
class MShapeComponent : public MSceneComponent
{
protected:
	std::vector<std::shared_ptr<FShape>> Shapes;
public:
	virtual void Render(SDL_Renderer* Renderer, FVector2D OnScreenLocation, float Zoom) const;

	void AddShape(std::shared_ptr<FShape> NewShape) { Shapes.push_back(NewShape); }

	void ClearShapes();

};

