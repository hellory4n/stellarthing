package core

// rectangle.
type Rect struct {
	X, Y, W, H float64
}

// returns the area of the rectangle
func (r Rect) Area() float64 {
	return r.W * r.H
}

// if true, the rects intersect with each other
func (a Rect) Intersects(b Rect) bool {
	// man
	if a.X >= (b.X + b.W) {
		return false
	}
	if (a.X + a.W) <= b.Y {
		return false
	}
	if a.Y >= (b.Y + b.H) {
		return false
	}
	if (a.Y + a.H) <= b.Y {
		return false
	}
	return true
}

// if true, the rect, in fact, has that point
func (r Rect) HasPoint(p Vec2) bool {
	if p.X < r.X {
		return false
	}
	if p.Y < r.Y {
		return false
	}

	if p.X >= (r.X + r.W) {
		return false
	}
	if p.Y >= (r.Y + r.H) {
		return false
	}

	return true
}
