package main

import (
	"github.com/hellory4n/stellarthing/core"
	"github.com/hellory4n/stellarthing/entities"
	"github.com/hellory4n/stellarthing/platform"
	"github.com/hellory4n/stellarthing/platform/audio"
	"github.com/hellory4n/stellarthing/platform/graphics"
	"github.com/hellory4n/stellarthing/species"
	"github.com/hellory4n/stellarthing/ui"
	"github.com/hellory4n/stellarthing/util"
)

func main() {
	platform.OpenWindow("Stellarthing", core.NewVec2i(1280, 720))
	defer platform.CloseWindow()
	// the game's actual resolution is scaled with high dpi so it doesnt matter :)
	core.RenderSize = core.NewVec2i(1280, 720)
	graphics.Init()
	defer graphics.Free()
	defer graphics.FreeAllTextures()

	ui.LoadTheme()
	defer ui.FreeTheme()

	audio.Init()
	defer audio.FreeAllAudio()

	entities.Init()
	defer entities.Free()

	var player *species.Player = new(species.Player)
	entities.AddEntity(player)

	for !platform.Closing() {
		// ha
		util.UpdateAllTimers()
		if platform.IsKeyJustPressed(platform.KeyF11) {
			platform.ToggleFullscreen()
		}

		graphics.Clear(core.ColorBlack)
		ui.UpdateInputFieldsFrfrfrThisTime()
		entities.UpdateAllEntities()
		graphics.EndDrawing()
	}
}
