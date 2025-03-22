#pragma once
#include "core/core.h"
#include "core/math/vec.h"

/// Rectangle.
typedef struct {
	f64 x;
	f64 y;
	f64 w;
	f64 h;
} StRect;

/// Returns the area of the rectangle.
f64 StRect_area(StRect r);

/// If true, the 2 rects intersect.
bool StRect_intersects(StRect a, StRect b);

/// If true, the rect, in fact, has that point
bool StRect_has_point(StRect rect, StVec2 point);
