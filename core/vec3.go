package core

import (
	"fmt"
	"math"
)

// 3D point with floats
type Vec3 struct {
	X float64
	Y float64
	Z float64
}

func NewVec3(x float64, y float64, z float64) Vec3 {
	return Vec3{X: x, Y: y, Z: z}
}

func (v Vec3) String() string {
	return fmt.Sprintf("%f, %f, %f", v.X, v.Y, v.Z)
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