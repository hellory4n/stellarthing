package main

import (
	"github.com/hellory4n/stellarthing/core"
	"github.com/hellory4n/stellarthing/game/species"
	"github.com/hellory4n/stellarthing/modules/audio"
	"github.com/hellory4n/stellarthing/modules/entities"
	"github.com/hellory4n/stellarthing/modules/graphics"
	"github.com/hellory4n/stellarthing/modules/platform"
	"github.com/hellory4n/stellarthing/modules/util"
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
