#pragma once
#include "PCH.h"

struct FBox
{
	FVector2D BoundMin;
	FVector2D BoundMax;

	/** Set correct min and max */
	void Normalize();

	bool IsIntersects(FBox OtherBox) const;
};

