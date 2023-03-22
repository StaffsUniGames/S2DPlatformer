#include "RectangleExtensions.h"

#include <cmath>

namespace RectangleExtensions
{
	Vector2 RectangleExtensions::GetIntersectionDepth(S2D::Rect* rectA, S2D::Rect* rectB)
	{
		// Calculate half sizes.
        float halfWidthA = rectA->Width / 2.0f;
        float halfHeightA = rectA->Height / 2.0f;
        float halfWidthB = rectB->Width / 2.0f;
        float halfHeightB = rectB->Height / 2.0f;

        // Calculate centers.
        Vector2* centerA = new Vector2(rectA->Left() + halfWidthA, rectA->Top() + halfHeightA);
        Vector2* centerB = new Vector2(rectB->Left() + halfWidthB, rectB->Top() + halfHeightB);

        // Calculate current and minimum-non-intersecting distances between centers.
		float distanceX = centerA->X - centerB->X;
		float distanceY = centerA->Y - centerB->Y;
        float minDistanceX = halfWidthA + halfWidthB;
        float minDistanceY = halfHeightA + halfHeightB;

        // If we are not intersecting at all, return (0, 0).
        if (abs(distanceX) >= minDistanceX || abs(distanceY) >= minDistanceY)
            return *Vector2::Zero;

        // Calculate and return intersection depths.
        float depthX = distanceX > 0 ? minDistanceX - distanceX : -minDistanceX - distanceX;
        float depthY = distanceY > 0 ? minDistanceY - distanceY : -minDistanceY - distanceY;
        return Vector2(depthX, depthY);
	}

	Vector2 RectangleExtensions::GetBottomCenter(S2D::Rect* rect)
	{
		return Vector2(rect->X + rect->Width / 2.0f, rect->Bottom());
	}
};