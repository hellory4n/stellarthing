// common functionality for the engine
package core

import (
	"fmt"
	"math"
)

// 2D point with floats
type Vec2 struct {
	X float64
	Y float64
}

func (v Vec2) String() string {
	return fmt.Sprintf("%f, %f", v.X, v.Y)
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

// 2D point with ints
type Vec2i struct {
	X int64
	Y int64
}

func (v Vec2i) String() string {
	return fmt.Sprintf("%d, %d", v.X, v.Y)
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

// 3D point with floats
type Vec3 struct {
	X float64
	Y float64
	Z float64
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

// 3D point with floats
type Vec3i struct {
	X int64
	Y int64
	Z int64
}

func (v Vec3i) String() string {
	return fmt.Sprintf("%d, %d, %d", v.X, v.Y, v.Z)
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