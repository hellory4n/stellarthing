package util

import (
	"fmt"
	"math"
	"runtime"

	rl "github.com/gen2brain/raylib-go/raylib"
	"github.com/hellory4n/stellarthing/core"
	"github.com/hellory4n/stellarthing/platform"
	"github.com/hellory4n/stellarthing/platform/graphics"
	"github.com/hellory4n/stellarthing/ui"
)

var debugMode bool = false

// yeah
func UpdateDebugMode() {
	if platform.IsKeyJustPressed(platform.KeyF3) {
		debugMode = !debugMode
	}
	if !debugMode {
		return
	}

	var m runtime.MemStats
    runtime.ReadMemStats(&m)

	// DEATH
	text := fmt.Sprintf(
		"Stellarthing %v - Starry %v\n\n%v FPS\nHeap: %v MiB\nCumulative alloc: %v MiB\n" +
		"Reserved memory: %v MiB\nGC cycles: %v",
		core.GameVersionStr, core.StarryVersionStr, rl.GetFPS(), m.Alloc / 1024 / 1024,
		m.TotalAlloc / 1024 / 1024, m.Sys / 1024 / 1024, m.NumGC,
	)

	// tile-bloody-map
	if graphics.CurrentWorld != nil {
		text = fmt.Sprintf(
			"%v\n\nTilemap camera: %v\nLoaded ground tiles: %v (~%v chunks)\n" +
			"Loaded object tiles: %v (~%v chunks)\nCurrent chunk: %v",
			text, graphics.CurrentWorld.CameraPosition,
			len(graphics.CurrentWorld.LoadedGroundTiles),
			int64(len(graphics.CurrentWorld.LoadedGroundTiles)) / graphics.ChunkSize / graphics.ChunkSize,
			len(graphics.CurrentWorld.LoadedObjectTiles),
			int64(len(graphics.CurrentWorld.LoadedObjectTiles)) / graphics.ChunkSize / graphics.ChunkSize,
			// i dont even
			core.NewVec3i(int64(math.Floor(graphics.CurrentWorld.CameraPosition.X / float64(graphics.ChunkSize))), int64(math.Floor(graphics.CurrentWorld.CameraPosition.Y / float64(graphics.ChunkSize))), int64(graphics.CurrentWorld.CameraPosition.Z)),
		)
	}

	// man
	ui.DrawRegularText(text, core.NewVec2(18, 18), ui.DefaultFontSize, core.ColorBlack)
	ui.DrawRegularText(text, core.NewVec2(16, 16), ui.DefaultFontSize, core.ColorWhite)
}