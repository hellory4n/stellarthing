package main

import (
	"fmt"

	"github.com/hellory4n/stellarthing/core"
	"github.com/hellory4n/stellarthing/modules/platform"
	rl "github.com/gen2brain/raylib-go/raylib"
)

func main() {
	platform.OpenWindow("Stellarthing", core.NewVec2i(800, 600))
	platform.ToggleFullscreen()

	for !platform.Closing() {
		rl.BeginDrawing()
		rl.ClearBackground(rl.White)
		if platform.IsKeyJustPressed(platform.KeySpace) {
			fmt.Println("hi mom")
		}
		rl.EndDrawing()
	}

	platform.CloseWindow()
}
