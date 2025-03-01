package main

import (
	"github.com/hellory4n/stellarthing/core"
	"github.com/hellory4n/stellarthing/modules/graphics"
	"github.com/hellory4n/stellarthing/modules/platform"
)

func main() {
	platform.OpenWindow("Stellarthing", core.NewVec2i(800, 600))
	platform.ToggleFullscreen()

	texture := graphics.LoadTexture("assets/bob_guy.png")

	for !platform.Closing() {
		graphics.Clear(core.ColorBlack)
		graphics.DrawTexture(texture, core.NewVec2(60, 60), 65, core.ColorWhite)
		graphics.EndDrawing()
	}

	graphics.FreeAllTextures()
	platform.CloseWindow()
}
