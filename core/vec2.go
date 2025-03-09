// common functionality for the engine
package core

import (
	"fmt"
	"math"
)

// 2D point with floats
type Vec2 struct {
	X, Y float64
}

func NewVec2(x float64, y float64) Vec2 {
	return Vec2{X: x, Y: y}
}

func (v Vec2) String() string {
	return fmt.Sprintf("vec2(%f, %f)", v.X, v.Y)
}

// adds
func (a Vec2) Add(b Vec2) Vec2 {
	return Vec2{a.X + b.X, a.Y + b.Y}
}

// subtracts
func (a Vec2) Sub(b Vec2) Vec2 {
	return Vec2{a.X - b.X, a.Y - b.Y}
}

// multiplies by a vec2
func (a Vec2) Mul(b Vec2) Vec2 {
	return Vec2{a.X * b.X, a.Y * b.Y}
}

// multiplies by a float
func (a Vec2) Smul(b float64) Vec2 {
	return Vec2{a.X * b, a.Y * b}
}

// divides by a vec2
func (a Vec2) Div(b Vec2) Vec2 {
	return Vec2{a.X / b.X, a.Y / b.Y}
}

// divides by a float
func (a Vec2) Sdiv(b float64) Vec2 {
	return Vec2{a.X / b, a.Y / b}
}

// modulo
func (a Vec2) Mod(b Vec2) Vec2 {
	return Vec2{math.Mod(a.X, b.X), math.Mod(a.X, b.X)}
}

// less than
func (a Vec2) Lt(b Vec2) bool {
	return a.X < b.X && a.Y < b.Y
}

// less than or equal to
func (a Vec2) Lte(b Vec2) bool {
	return a.X <= b.X && a.Y <= b.Y
}

// greater than
func (a Vec2) Gt(b Vec2) bool {
	// shout out to lua
	return b.Lt(a)
}

// greater than or equal to
func (a Vec2) Gte(b Vec2) bool {
	return b.Lte(a)
}

// equal
func (a Vec2) Eq(b Vec2) bool {
	return a.X == b.X && a.Y == b.Y
}

// not equal
func (a Vec2) Neq(b Vec2) bool {
	return !a.Eq(b)
}

// negate
func (a Vec2) Neg() Vec2 {
	return Vec2{-a.X, -a.Y}
}

// converts the vector to a vec2i
func (a Vec2) ToVec2i() Vec2i {
	return Vec2i{X: int64(a.X), Y: int64(a.Y)}
}