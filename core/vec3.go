package core

import (
	"fmt"
	"math"
)

// 3D point with floats
type Vec3 struct {
	X, Y, Z float64
}

func (v Vec3) String() string {
	return fmt.Sprintf("vec3(%f, %f, %f)", v.X, v.Y, v.Z)
}

// adds
func (a Vec3) Add(b Vec3) Vec3 {
	return Vec3{a.X + b.X, a.Y + b.Y, a.Z + b.Z}
}

// subtracts
func (a Vec3) Sub(b Vec3) Vec3 {
	return Vec3{a.X - b.X, a.Y - b.Y, a.Z - b.Z}
}

// multiplies by a vec3
func (a Vec3) Mul(b Vec3) Vec3 {
	return Vec3{a.X * b.X, a.Y * b.Y, a.Z * b.Z}
}

// multiplies by a float
func (a Vec3) Smul(b float64) Vec3 {
	return Vec3{a.X * b, a.Y * b, a.Z * b}
}

// divides by a vec3
func (a Vec3) Div(b Vec3) Vec3 {
	return Vec3{a.X / b.X, a.Y / b.Y, a.Z / b.Z}
}

// divides by a float
func (a Vec3) Sdiv(b float64) Vec3 {
	return Vec3{a.X / b, a.Y / b, a.Z / b}
}

// modulo
func (a Vec3) Mod(b Vec3) Vec3 {
	return Vec3{math.Mod(a.X, b.X), math.Mod(a.X, b.X), math.Mod(a.Z, b.Z)}
}

// less than
func (a Vec3) Lt(b Vec3) bool {
	return a.X < b.X && a.Y < b.Y && a.Z < b.Z
}

// less than or equal to
func (a Vec3) Lte(b Vec3) bool {
	return a.X <= b.X && a.Y <= b.Y && a.Z <= b.Z
}

// greater than
func (a Vec3) Gt(b Vec3) bool {
	// shout out to lua
	return b.Lt(a)
}

// greater than or equal to
func (a Vec3) Gte(b Vec3) bool {
	return b.Lte(a)
}

// equal
func (a Vec3) Eq(b Vec3) bool {
	return a.X == b.X && a.Y == b.Y && a.Z == b.Z
}

// not equal
func (a Vec3) Neq(b Vec3) bool {
	return !a.Eq(b)
}

// negate
func (a Vec3) Neg() Vec3 {
	return Vec3{-a.X, -a.Y, -a.Z}
}

// as the name implies, it normalizes the vector
func (a Vec3) Normalize() Vec3 {
	magnitude := math.Sqrt(a.X*a.X + a.Y*a.Y + a.Z*a.Z)

	result := Vec3{a.X, a.Y, a.Z}
	if magnitude != 0 {
		result.X = result.X / magnitude
		result.Y = result.Y / magnitude
		result.Z = result.Z / magnitude
	}
	return result
}
