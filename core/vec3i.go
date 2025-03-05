package core

import "fmt"

// 3D point with floats
type Vec3i struct {
	X int64
	Y int64
	Z int64
}

func NewVec3i(x int64, y int64, z int64) Vec3i {
	return Vec3i{X: x, Y: y, Z: z}
}

func (v Vec3i) String() string {
	return fmt.Sprintf("vec3i(%d, %d, %d)", v.X, v.Y, v.Z)
}

// adds
func (a Vec3i) Add(b Vec3i) Vec3i {
	return Vec3i{a.X + b.X, a.Y + b.Y, a.Z + b.Z}
}

// subtracts
func (a Vec3i) Sub(b Vec3i) Vec3i {
	return Vec3i{a.X - b.X, a.Y - b.Y, a.Z - b.Z}
}

// multiplies by a vec3i
func (a Vec3i) Mul(b Vec3i) Vec3i {
	return Vec3i{a.X * b.X, a.Y * b.Y, a.Z * b.Z}
}

// multiplies by an int
func (a Vec3i) Smul(b int64) Vec3i {
	return Vec3i{a.X * b, a.Y * b, a.Z * b}
}

// divides by a vec3i
func (a Vec3i) Div(b Vec3i) Vec3i {
	return Vec3i{a.X / b.X, a.Y / b.Y, a.Z / b.Z}
}

// divides by a float
func (a Vec3i) Sdiv(b int64) Vec3i {
	return Vec3i{a.X / b, a.Y / b, a.Z / b}
}

// modulo
func (a Vec3i) Mod(b Vec3i) Vec3i {
	return Vec3i{a.X % b.X, a.X % b.X, a.Z % b.Z}
}

// less than
func (a Vec3i) Lt(b Vec3i) bool {
	return a.X < b.X && a.Y < b.Y && a.Z < b.Z
}

// less than or equal to
func (a Vec3i) Lte(b Vec3i) bool {
	return a.X <= b.X && a.Y <= b.Y && a.Z <= b.Z
}

// greater than
func (a Vec3i) Gt(b Vec3i) bool {
	// shout out to lua
	return b.Lt(a)
}

// greater than or equal to
func (a Vec3i) Gte(b Vec3i) bool {
	return b.Lte(a)
}

// equal
func (a Vec3i) Eq(b Vec3i) bool {
	return a.X == b.X && a.Y == b.Y && a.Z == b.Z
}

// not equal
func (a Vec3i) Neq(b Vec3i) bool {
	return !a.Eq(b)
}

// negate
func (a Vec3i) Neg() Vec3i {
	return Vec3i{-a.X, -a.Y, -a.Z}
}