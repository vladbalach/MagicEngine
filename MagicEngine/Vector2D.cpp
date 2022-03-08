#include "Vector2D.h"
#include "Box.h"

bool FVector2D::IsInBounds(FBox Bounds) const
{
	Bounds.Normalize();

	return X >= Bounds.BoundMin.X && X <= Bounds.BoundMax.X
		&& Y >= Bounds.BoundMin.Y && Y <= Bounds.BoundMax.Y;
}

float FVector2D::DistSqr(FVector2D Start, FVector2D Finish)
{
	return (Start.X - Finish.X) * (Start.X - Finish.X) + (Start.Y - Finish.Y) * (Start.Y - Finish.Y);
}

float FVector2D::Dist(FVector2D Start, FVector2D Finish)
{
	return sqrt((Start.X - Finish.X) * (Start.X - Finish.X) + (Start.Y - Finish.Y) * (Start.Y - Finish.Y));
}

void Swap(FVector2D& A, FVector2D& B) {
	FVector2D buff = A;
	A = B;
	B = buff;
}
