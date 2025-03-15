package main

import (
	"log"
	"os"
	"runtime/pprof"

	"github.com/hellory4n/stellarthing/core"
	"github.com/hellory4n/stellarthing/core/util"
	"github.com/hellory4n/stellarthing/entity"
	"github.com/hellory4n/stellarthing/platform"
	"github.com/hellory4n/stellarthing/platform/audio"
	"github.com/hellory4n/stellarthing/platform/graphics"
	"github.com/hellory4n/stellarthing/player"
	"github.com/hellory4n/stellarthing/tile"
	"github.com/hellory4n/stellarthing/ui"
)

func main() {
	platform.OpenWindow("stellarthing", core.Vec2i{1280, 720})
	defer platform.CloseWindow()
	// the game's actual resolution is scaled with high dpi so it doesnt matter :)
	core.RenderSize = core.Vec2i{1280, 720}
	graphics.Init()
	defer graphics.Free()
	defer graphics.FreeAllTextures()

	ui.LoadTheme()
	defer ui.FreeTheme()

	audio.Init()
	defer audio.FreeAllAudio()

	entity.Init()
	defer entity.Free()

	var player *player.Player = &player.Player{}
	entity.Add(player)

	for !platform.Closing() {
		// ha
		util.UpdateAllTimers()
		if platform.IsKeyJustPressed(platform.KeyF11) {
			platform.ToggleFullscreen()
		}

		graphics.Clear(core.ColorBlack)
		if tile.ThisWorld != nil {
			tile.ThisWorld.Draw()
		}

		// man
		entity.UpdateAll()
		core.InternalInputFieldFocus = false
		util.UpdateDebugMode()
		graphics.EndDrawing()
	}

	f, err := os.Create("heap.prof")
	if err != nil {
		log.Fatal(err)
	}
	pprof.WriteHeapProfile(f)
	f.Close()
}
