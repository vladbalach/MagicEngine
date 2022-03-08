#pragma once
#include <cstdint>


struct FBox;

struct FVector2D {
	float X = 0.f;
	float Y = 0.f;

	FVector2D operator +(const FVector2D& vec) const {
		return FVector2D{ X + vec.X, Y + vec.Y };
	}

	FVector2D operator -(const FVector2D& vec) const {
		return FVector2D{ X - vec.X, Y - vec.Y };
	}

	FVector2D operator *(float l) const {
		return FVector2D{ X * l, Y * l };
	}

	FVector2D operator /(float l) const {
		return FVector2D{ X / l, Y / l };
	}

	/** Returns true if this poitn in bounds*/
	inline bool IsInBounds(FVector2D BoundMin, FVector2D BoundMax) {

		// normalize box
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

		return X >= BoundMin.X && X <= BoundMax.X
			&& Y >= BoundMin.Y && Y <= BoundMax.Y;
	}

	/* < and >, not >= and <= */
	bool IsInBoundsHard(FVector2D BoundMin, FVector2D BoundMax) {

		// normalize box
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

		return X > BoundMin.X && X < BoundMax.X
			&& Y > BoundMin.Y && Y < BoundMax.Y;
	}

	bool IsInBounds(FBox Bounds) const;

	static float DistSqr(FVector2D Start, FVector2D Finish);
	static float Dist(FVector2D Start, FVector2D Finish);
};


void Swap(FVector2D& A, FVector2D& B);

