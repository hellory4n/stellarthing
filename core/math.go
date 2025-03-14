package core

import (
	"math"
	"math/rand"
	"strings"
	"time"
)

const Int32Min int32 = -2147483648
const Int32Max int32 = 2147483647
const Uint32Min uint32 = 0
const Uint32Max uint32 = 4294967295

var randGen *rand.Rand

func init() {
	// seed :)
	randGen = rand.New(rand.NewSource(time.Now().UnixNano()))
}

// converts degrees to radians
func DegToRad(deg float64) float64 {
	return deg * (math.Pi / 180.0)
}

// converts radians to degrees
func RadToDeg(rad float64) float64 {
	return rad * (180 / math.Pi)
}

// clamp
func Clamp(val float64, min float64, max float64) float64 {
	return math.Max(min, math.Min(val, max))
}

func RandInt(min int, max int) int {
	return randGen.Intn(max-min) + min
}

func RandFloat(min float64, max float64) float64 {
	return (randGen.Float64() * max) + min
}

func RandUint32(min uint32, max uint32) uint32 {
	return (randGen.Uint32() % (max - min)) + min
}

// makes a random base64 string (similar to youtube IDs)
func RandBase64(length int) string {
	const chars string = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_"
	var x strings.Builder
	x.Grow(length)
	for range length {
		x.WriteRune(rune(RandInt(0, len(chars))))
	}
	return x.String()
}
