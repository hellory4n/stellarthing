package main

import (
	"github.com/hellory4n/stellarthing/core"
	"github.com/hellory4n/stellarthing/species"
	"github.com/hellory4n/stellarthing/platform/audio"
	"github.com/hellory4n/stellarthing/entities"
	"github.com/hellory4n/stellarthing/platform/graphics"
	"github.com/hellory4n/stellarthing/platform"
	"github.com/hellory4n/stellarthing/util"
)

func main() {
	platform.OpenWindow("Stellarthing", core.NewVec2i(1920, 1080))
	defer platform.CloseWindow()
	platform.ToggleFullscreen()

	audio.Init()
	defer audio.FreeAllAudio()

	entities.Init()
	defer entities.Free()

	var player *species.Player = new(species.Player)
	entities.AddEntity(player)

	for !platform.Closing() {
		graphics.Clear(core.ColorBlack)
		entities.UpdateAllEntities()
		graphics.EndDrawing()

		util.UpdateAllTimers()
	}

	graphics.FreeAllTextures()
}
