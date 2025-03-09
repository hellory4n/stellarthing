package core

import "fmt"

// 2D point with ints
type Vec2i struct {
	X, Y int64
}

func NewVec2i(x int64, y int64) Vec2i {
	return Vec2i{X: x, Y: y}
}

func (v Vec2i) String() string {
	return fmt.Sprintf("vec2i(%d, %d)", v.X, v.Y)
}

// adds
func (a Vec2i) Add(b Vec2i) Vec2i {
	return Vec2i{a.X + b.X, a.Y + b.Y}
}

// subtracts
func (a Vec2i) Sub(b Vec2i) Vec2i {
	return Vec2i{a.X - b.X, a.Y - b.Y}
}

// multiplies by a vec2i
func (a Vec2i) Mul(b Vec2i) Vec2i {
	return Vec2i{a.X * b.X, a.Y * b.Y}
}

// multiplies by an int
func (a Vec2i) Smul(b int64) Vec2i {
	return Vec2i{a.X * b, a.Y * b}
}

// divides by a vec2i
func (a Vec2i) Div(b Vec2i) Vec2i {
	return Vec2i{a.X / b.X, a.Y / b.Y}
}

// divides by an int
func (a Vec2i) Sdiv(b int64) Vec2i {
	return Vec2i{a.X / b, a.Y / b}
}

// modulo
func (a Vec2i) Mod(b Vec2i) Vec2i {
	return Vec2i{a.X % b.X, a.X % b.X}
}

// less than
func (a Vec2i) Lt(b Vec2i) bool {
	return a.X < b.X && a.Y < b.Y
}

// less than or equal to
func (a Vec2i) Lte(b Vec2i) bool {
	return a.X <= b.X && a.Y <= b.Y
}

// greater than
func (a Vec2i) Gt(b Vec2i) bool {
	// shout out to lua
	return b.Lt(a)
}

// greater than or equal to
func (a Vec2i) Gte(b Vec2i) bool {
	return b.Lte(a)
}

// equal
func (a Vec2i) Eq(b Vec2i) bool {
	return a.X == b.X && a.Y == b.Y
}

// not equal
func (a Vec2i) Neq(b Vec2i) bool {
	return !a.Eq(b)
}

// negate
func (a Vec2i) Neg() Vec2i {
	return Vec2i{-a.X, -a.Y}
}

// converts the vector to a vec2
func (a Vec2i) ToVec2() Vec2 {
	return Vec2{X: float64(a.X), Y: float64(a.Y)}
}