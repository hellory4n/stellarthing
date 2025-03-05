package graphics

import "github.com/hellory4n/stellarthing/core"

// it's tile data
type TileData struct {
	// path for the string, loaded by the renderer then put in the Texture cache
	Texture string
	// used for moving entities
	Position core.Vec3
	// man
	UsingCustomPos bool
	// lol
	Tint core.Color
}

// yeah
type TileId uint32
// tiles can have variations. the default variation is always 0
type VariationId uint32

const TileAir TileId = 0
const TileBobGuy TileId = 370779849
const TileMarsRock TileId = 2370611866

// tile data from IDs and variations
var Tiles map[TileId]map[VariationId]TileData = map[TileId]map[VariationId]TileData{
	TileAir: {
		0: TileData{
			Texture: "assets/air.png",
			Tint: core.ColorWhite,
		},
	},
	TileBobGuy: {
		0: TileData{
			Texture: "assets/bob_guy.png",
			Tint: core.ColorWhite,
		},
	},
	TileMarsRock: {
		0: TileData{
			Texture: "assets/mars_rock.png",
			Tint: core.ColorWhite,
		},
	},
}

// printable tile IDs so i don't have to memorize 2370611866
var TileNames map[TileId]string = map[TileId]string{
	TileAir: "stellarthing:Air",
	TileBobGuy: "stellarthing:BobGuy",
	TileMarsRock: "stellarthing:MarsRock",
}