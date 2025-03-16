package util

import (
	"fmt"
	"math"
	"runtime"

	rl "github.com/gen2brain/raylib-go/raylib"
	"github.com/hellory4n/stellarthing/core"
	"github.com/hellory4n/stellarthing/platform"
	"github.com/hellory4n/stellarthing/tile"
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
		"Stellarthing %v - Starry %v\n\n%v FPS\nHeap: %v MiB\nCumulative alloc: %v MiB\n"+
			"Reserved memory: %v MiB\nGC cycles: %v",
		core.GameVersionStr, core.StarryVersionStr, rl.GetFPS(), m.Alloc/1024/1024,
		m.TotalAlloc/1024/1024, m.Sys/1024/1024, m.NumGC,
	)

	// tile-bloody-map
	if tile.ThisWorld != nil {
		text = fmt.Sprintf(
			"%v\n\nTilemap camera: %v\nLoaded ground tiles: %v (~%v chunks)\n"+
				"Loaded object tiles: %v (~%v chunks)\nCurrent chunk: %v\nZoom: %v",
			text, tile.ThisWorld.CameraPosition,
			len(tile.ThisWorld.LoadedGroundTiles),
			int64(len(tile.ThisWorld.LoadedGroundTiles))/tile.ChunkSize/tile.ChunkSize,
			len(tile.ThisWorld.LoadedObjectTiles),
			int64(len(tile.ThisWorld.LoadedObjectTiles))/tile.ChunkSize/tile.ChunkSize,
			// i dont even
			core.Vec3i{
				int64(math.Floor(tile.ThisWorld.CameraPosition.X / float64(tile.ChunkSize))),
				int64(math.Floor(tile.ThisWorld.CameraPosition.Y / float64(tile.ChunkSize))),
				int64(tile.ThisWorld.CameraPosition.Z),
			},
			tile.ThisWorld.CameraScale,
		)
	}

	// man
	ui.DrawRegularText(text, core.Vec2{18, 18}, ui.DefaultFontSize, core.ColorBlack)
	ui.DrawRegularText(text, core.Vec2{16, 16}, ui.DefaultFontSize, core.ColorWhite)
}
