#include "Box.h"

void FBox::Normalize()
{
	if (BoundMin.X > BoundMax.X) {
		int32_t buff = BoundMin.X;
		BoundMin.X = BoundMax.X;
		BoundMax.X = buff;
	}

	if (BoundMin.Y > BoundMax.Y) {
		int32_t buff = BoundMin.Y;
		BoundMin.Y = BoundMax.Y;
		BoundMax.Y = buff;
	}
}

bool FBox::IsIntersects(FBox OtherBox) const
{
	FBox This = *this;
	This.Normalize();
	OtherBox.Normalize();

	// Check all 4 points
	FVector2D Point1 = { OtherBox.BoundMax.X, OtherBox.BoundMin.Y };
	FVector2D Point2 = { OtherBox.BoundMin.X, OtherBox.BoundMax.Y };

	return OtherBox.BoundMin.IsInBounds(This)
		|| OtherBox.BoundMax.IsInBounds(This)
		|| Point1.IsInBounds(This)
		|| Point2.IsInBounds(This);
}
