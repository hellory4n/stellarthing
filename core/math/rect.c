#include "rect.h"

f64 StRect_area(StRect r)
{
	return r.w * r.h;
}

bool StRect_intersects(StRect a, StRect b)
{
	// man
	if (a.x >= (b.x + b.w)) {
		return false;
	}
	if ((a.x + a.w) <= b.y) {
		return false;
	}
	if (a.y >= (b.y + b.h)) {
		return false;
	}
	if ((a.y + a.h) <= b.y) {
		return false;
	}
	return true;
}

bool StRect_has_point(StRect rect, StVec2 point)
{
	if (point.x < rect.x) {
		return false;
	}
	if (point.y < rect.y) {
		return false;
	}

	if (point.x >= (rect.x + rect.w)) {
		return false;
	}
	if (point.y >= (rect.y + rect.h)) {
		return false;
	}

	return true;
}
