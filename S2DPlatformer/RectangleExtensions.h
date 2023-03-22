#pragma once

#include "S2D\S2D.h"

using namespace S2D;

namespace RectangleExtensions
{
	Vector2 GetIntersectionDepth(S2D::Rect* rectA, S2D::Rect* rectB);
	Vector2 GetBottomCenter(S2D::Rect* rect);
};

