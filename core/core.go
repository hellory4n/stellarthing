package core

import "fmt"

// enables/disables some features such as assert
const Debug = true

// engine version
const StarryVersion = "v4.0.0"

// game version
const GameVersion = "v0.11.0"

// panics if a condition isn't met but only in debug. useful for not making dumb mistakes
func Assert(msg string, condition bool) {
	if !condition {
		panic(fmt.Sprintf("Assert failed: %v\n", msg))
	}
}