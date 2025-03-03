// platform :)
package platform

import (
	"fmt"

	rl "github.com/gen2brain/raylib-go/raylib"
	"github.com/hellory4n/stellarthing/core"
)

var closing bool = false
var ready bool = false

// opens a window
func OpenWindow(title string, size core.Vec2i) {
	rl.SetConfigFlags(rl.FlagVsyncHint | rl.FlagWindowResizable)
	rl.InitWindow(int32(size.X), int32(size.Y), title)
	rl.SetExitKey(rl.KeyNull)
	fmt.Println("[WINDOW] Window has been created")

	ready = true
}

// closes the window and frees everything. if you just want to kindly ask it to close, use `RequestClose`
func CloseWindow() {
	rl.CloseWindow()
	fmt.Println("[WINDOW] Window has been closed")
}

func RequestClose() {
	closing = true
	fmt.Println("[WINDOW] Requested to close")
}

// as the name implies, it toggles fullscreen
func ToggleFullscreen() {
	rl.ToggleFullscreen()
	fmt.Println("[WINDOW] Toggled fullscreen")
}

// if true, the window is closing
func Closing() bool {
	return closing || rl.WindowShouldClose()
}

// as the name implies, it sets the target FPS. useful on crap computers
func SetTargetFps(fps int) {
	rl.SetTargetFPS(int32(fps))
}

// if true, there is, in fact, a window (and opengl context)
func Ready() bool {
	return ready
}

// time in seconds since the window was opened
func TimeOpened() float64 {
	return rl.GetTime()
}

// returns the time in seconds between frames. useful for things to look the same no matter the frame rate. look up delta time.
func DeltaTime() float64 {
	return float64(rl.GetFrameTime())
}