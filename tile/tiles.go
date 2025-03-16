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
	Air          Id = 0
	BobGuy       Id = 370779849
	MarsRock     Id = 2370611866
	BlueGuy      Id = 3620194283
	GreenGuy     Id = 1097781405
	Life         Id = 4262882056
	DeepOcean    Id = 2994122863
	MidOcean     Id = 4127332781
	ShallowOcean Id = 2184219526
	LowGrass     Id = 2991591512
	HighGrass    Id = 994351604
	Sand         Id = 3777224164
	Stone        Id = 4041246397
	Mountain     Id = 2830581218
	Snow         Id = 692149091
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
	DeepOcean: {
		0: &TileData{
			Texture: "assets/deep_ocean.png",
			Tint:    core.ColorWhite,
		},
	},
	HighGrass: {
		0: &TileData{
			Texture: "assets/high_grass.png",
			Tint:    core.ColorWhite,
		},
	},
	LowGrass: {
		0: &TileData{
			Texture: "assets/low_grass.png",
			Tint:    core.ColorWhite,
		},
	},
	MidOcean: {
		0: &TileData{
			Texture: "assets/mid_ocean.png",
			Tint:    core.ColorWhite,
		},
	},
	Mountain: {
		0: &TileData{
			Texture: "assets/mountain.png",
			Tint:    core.ColorWhite,
		},
	},
	Sand: {
		0: &TileData{
			Texture: "assets/sand.png",
			Tint:    core.ColorWhite,
		},
	},
	ShallowOcean: {
		0: &TileData{
			Texture: "assets/shallow_ocean.png",
			Tint:    core.ColorWhite,
		},
	},
	Snow: {
		0: &TileData{
			Texture: "assets/snow.png",
			Tint:    core.ColorWhite,
		},
	},
	Stone: {
		0: &TileData{
			Texture: "assets/stone.png",
			Tint:    core.ColorWhite,
		},
	},
}

// printable tile IDs so i don't have to memorize 2370611866
var TileNames map[Id]string = map[Id]string{
	Air:          "stellarthing:Air",
	BobGuy:       "stellarthing:BobGuy",
	MarsRock:     "stellarthing:MarsRock",
	BlueGuy:      "stellarthing:BlueGuy",
	GreenGuy:     "stellarthing:GreenGuy",
	Life:         "stellarthing:Life",
	DeepOcean:    "stellarthing:DeepOcean",
	HighGrass:    "stellarthing:HighGrass",
	LowGrass:     "stellarthing:LowGrass",
	MidOcean:     "stellarthing:MidOcean",
	Mountain:     "stellarthing:Mountain",
	Sand:         "stellarthing:Sand",
	ShallowOcean: "stellarthing:ShallowOcean",
	Snow:         "stellarthing:Snow",
	Stone:        "stellarthing:Stone",
}
