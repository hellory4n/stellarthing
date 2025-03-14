package tile

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
type Id uint32

// tiles can have variations. the default variation is always 0
type Variation uint32

const (
	Air      Id = 0
	BobGuy      = 370779849
	MarsRock    = 2370611866
	BlueGuy     = 3620194283
	GreenGuy    = 1097781405
	Life        = 4262882056
)

// tile data from IDs and variations
var Tiles map[Id]map[Variation]*TileData = map[Id]map[Variation]*TileData{
	Air: {
		0: &TileData{
			Texture: "assets/air.png",
			Tint:    core.ColorWhite,
		},
	},
	BobGuy: {
		0: &TileData{
			Texture: "assets/bob_guy.png",
			Tint:    core.ColorWhite,
		},
	},
	MarsRock: {
		0: &TileData{
			Texture: "assets/mars_rock.png",
			Tint:    core.ColorWhite,
		},
	},
	BlueGuy: {
		0: &TileData{
			Texture: "assets/blue_guy.png",
			Tint:    core.ColorWhite,
		},
	},
	GreenGuy: {
		0: &TileData{
			Texture: "assets/green_guy.png",
			Tint:    core.ColorWhite,
		},
	},
	Life: {
		0: &TileData{
			Texture: "assets/life.png",
			Tint:    core.ColorWhite,
		},
	},
}

// printable tile IDs so i don't have to memorize 2370611866
var TileNames map[Id]string = map[Id]string{
	Air:      "stellarthing:Air",
	BobGuy:   "stellarthing:BobGuy",
	MarsRock: "stellarthing:MarsRock",
	BlueGuy:  "stellarthing:BlueGuy",
	GreenGuy: "stellarthing:GreenGuy",
	Life:     "stellarthing:Life",
}
