package core

// rectangle.
type Rect struct {
	Pos, Size Vec2
}

// as the name implies, it makes a new rectangle
func NewRect(x, y, w, h float64) Rect {
	return Rect{Pos: NewVec2(x, y), Size: NewVec2(w, h)}
}

// returns the area of the rectangle
func (r Rect) Area() float64 {
	return r.Size.X * r.Size.Y
}

// if true, the rects intersect with each other
func (a Rect) Intersects(b Rect) bool {
	// man
	if a.Pos.X >= (b.Pos.X + b.Size.X) {
		return false
	}
	if (a.Pos.X + a.Size.X) <= b.Pos.Y {
		return false
	}
	if a.Pos.Y >= (b.Pos.Y + b.Size.Y) {
		return false
	}
	if (a.Pos.Y + a.Size.Y) <= b.Pos.Y {
		return false
	}
	return true
}

// if true, the rect, in fact, has that point
func (r Rect) HasPoint(p Vec2) bool {
	if p.X < r.Pos.X {
		return false
	}
	if p.Y < r.Pos.Y {
		return false
	}

	if p.X >= (r.Pos.X + r.Size.X) {
		return false
	}
	if p.Y >= (r.Pos.Y + r.Size.Y) {
		return false
	}

	return true
}