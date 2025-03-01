package main

import (
	"github.com/hellory4n/stellarthing/core"
	"github.com/hellory4n/stellarthing/modules/audio"
	"github.com/hellory4n/stellarthing/modules/graphics"
	"github.com/hellory4n/stellarthing/modules/platform"
)

func main() {
	platform.OpenWindow("Stellarthing", core.NewVec2i(800, 600))
	platform.ToggleFullscreen()
	audio.Init()

	texture := graphics.LoadTexture("assets/bob_guy.png")
	audio.SetListener(core.NewVec3(0, 0, 0))
	bob := audio.LoadAudio("assets/ross_tibeeth_jr_hhhh.ogg")
	bobb := audio.LoadAudio("assets/ross_tibeeth_jr_hhhh.ogg")
	bob.SetPosition(core.NewVec3(-5, 5, 0))
	bobb.SetPosition(core.NewVec3(50, 50, 0))
	bob.Play()
	bobb.Play()

	var pausema bool = false

	for !platform.Closing() {
		if platform.IsKeyJustPressed(platform.KeyNum8) {
			pausema = !pausema
			bob.Pause(pausema)
		}
		graphics.Clear(core.ColorBlack)
		graphics.DrawTexture(texture, core.NewVec2(60, 60), 65, core.ColorWhite)
		graphics.EndDrawing()
	}

	audio.FreeAllAudio()
	graphics.FreeAllTextures()
	platform.CloseWindow()
}
