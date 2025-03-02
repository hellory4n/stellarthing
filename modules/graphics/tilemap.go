package graphics

import (
	"fmt"
	"math"

	"github.com/hellory4n/stellarthing/core"
)

// how down can you go
const MinLayer int = -64

// how up can you go
const MaxLayer int = 256

// mate
const TotalLayers int = 320

// chunk size (they're square)
const ChunkSize int = 16

// it's a tile. use with TileWorld
type Tile struct {
	// z is the layer
	Position core.Vec3
	// el scorcho! AY CABRÓN
	Tint core.Color
	// i have 3 sides... i'm a triangle
	Side uint8
	// if true, the tile is in fact no tile. default for tiles until you fill them with something
	Empty bool
	// textures. order doesn't really matter
	Textures [4]Texture
}

// as the name implies, it's a world of tiles... truly gives a world of possibilities HAHAHBAHAHAHHAHAAHHAAHEHOEGOHHKHRTIJOHYJIORIOGREFYH;TPHOY;IFPPIKPGPJOILKṔ;Ó[;O]-;I90;[-P89P0689;0-P69]P´[9]0]
type TileWorld struct {
	// it's a hashmap of chunk positions and an array of their layers, each with a 2d array of tiles
	ground map[core.Vec2i][TotalLayers][ChunkSize][ChunkSize]Tile
	objects map[core.Vec2i][TotalLayers][ChunkSize][ChunkSize]Tile
	currentChunk core.Vec2i
	currentLayer int
	cameraPosition core.Vec2
	cameraScale core.Vec2
}

// current world
var CurrentWorld *TileWorld

// makes a new world :)
func NewTileWorld(minChunk core.Vec2i, maxChunk core.Vec2i) *TileWorld {
	var world *TileWorld = new(TileWorld)

	// this may be one of the worst things ive ever done
	world.ground = make(map[core.Vec2i][320][16][16]Tile)
	for y := minChunk.Y; y < maxChunk.Y; y++ {
		for x := minChunk.X; x < maxChunk.X; x++ {
			world.ground[core.NewVec2i(x, y)] = [TotalLayers][ChunkSize][ChunkSize]Tile{}
		}
	}

	world.objects = make(map[core.Vec2i][320][16][16]Tile)
	for y := minChunk.Y; y < maxChunk.Y; y++ {
		for x := minChunk.X; x < maxChunk.X; x++ {
			world.objects[core.NewVec2i(x, y)] = [TotalLayers][ChunkSize][ChunkSize]Tile{}
		}
	}

	fmt.Println("[TILEMAP] World created")
	return world
}

// adds a tile
func (t *TileWorld) AddTile(pos core.Vec3, ground bool, side0 Texture, side1 Texture, side2 Texture, side3 Texture) *Tile {
	var tile *Tile = t.GetTile(pos, ground)
	core.Assert("tile != nil", tile != nil)

	tile.Empty = false
	tile.Position = pos
	tile.Tint = core.ColorWhite
	tile.Textures[0] = side0
	tile.Textures[1] = side1
	tile.Textures[2] = side2
	tile.Textures[3] = side3
    return tile
}

// gets a tile
func (t *TileWorld) GetTile(pos core.Vec3, ground bool) *Tile {
	var chunk [TotalLayers][ChunkSize][ChunkSize]Tile
	if ground {
		chunk = t.ground[
			core.NewVec2i(int64(math.Floor(pos.X / float64(ChunkSize))), int64(math.Floor(pos.Y / float64(ChunkSize))))]
	} else {
		chunk = t.objects[
			core.NewVec2i(int64(math.Floor(pos.X / float64(ChunkSize))), int64(math.Floor(pos.Y / float64(ChunkSize))))]
	}

	var offsettedLayer int = int(core.Clamp(math.Round(pos.Z) + -float64(MinLayer),
		float64(MinLayer), float64(MaxLayer)))
	var layer [ChunkSize][ChunkSize]Tile = chunk[offsettedLayer]

	return &layer[int(math.Floor(pos.X))][int(math.Floor(pos.Y))]
}

// sets the camera position as well as the current chunk and layer
func (t *TileWorld) SetCameraPos(pos core.Vec3) {
	t.cameraPosition = core.NewVec2(pos.X, pos.Y)
	t.currentChunk = core.NewVec2(pos.X, pos.Y).Sdiv(float64(ChunkSize)).ToVec2i()
	t.currentLayer = int(math.Round(pos.Z))
}

// sets the camera scale. it's a multiplier so 1, 1 is the original scale
func (t *TileWorld) SetCameraScale(scale core.Vec2) {
	t.cameraScale = scale
}

func (t *TileWorld) drawChunk(offset core.Vec2i) {
	// here at shell we are sad
	for y := t.currentChunk.Y + offset.Y; y < t.currentChunk.Y + offset.Y + int64(ChunkSize); y++ {
		for x := t.currentChunk.X + offset.X; x < t.currentChunk.X + offset.X + int64(ChunkSize); x++ {
			// render ground tiles
			var tile *Tile = t.GetTile(core.NewVec3(float64(x), float64(y), float64(t.currentLayer)), true)
			var transformed core.Vec2 = core.NewVec2(tile.Position.X, tile.Position.Y).
				Add(t.cameraPosition).
				Mul(tile.Textures[tile.Side].Size().ToVec2()).
				Mul(t.cameraScale)
			
			DrawTextureExt(
				tile.Textures[tile.Side],
				core.NewVec2(0, 0),
				tile.Textures[tile.Side].Size().ToVec2(),
				transformed,
				tile.Textures[tile.Side].Size().ToVec2().Mul(t.cameraScale),
				core.NewVec2(0, 0), 0, tile.Tint,
			)

			// render object tiles
			var til *Tile = t.GetTile(core.NewVec3(float64(x), float64(y), float64(t.currentLayer)), true)
			var transforme core.Vec2 = core.NewVec2(til.Position.X, til.Position.Y).
				Add(t.cameraPosition).
				Mul(til.Textures[til.Side].Size().ToVec2()).
				Mul(t.cameraScale)
			
			DrawTextureExt(
				til.Textures[til.Side],
				core.NewVec2(0, 0),
				til.Textures[til.Side].Size().ToVec2(),
				transforme,
				til.Textures[til.Side].Size().ToVec2().Mul(t.cameraScale),
				core.NewVec2(0, 0), 0, til.Tint,
			)
		}
	}
}

// seeing is a core mechanic of Stellarballs
func (t *TileWorld) Draw() {
	t.drawChunk(core.NewVec2i(-1, -1))
	t.drawChunk(core.NewVec2i( 0, -1))
	t.drawChunk(core.NewVec2i( 1, -1))
	t.drawChunk(core.NewVec2i(-1,  0))
	t.drawChunk(core.NewVec2i( 0,  0))
	t.drawChunk(core.NewVec2i( 1,  0))
	t.drawChunk(core.NewVec2i(-1,  1))
	t.drawChunk(core.NewVec2i( 0,  1))
	t.drawChunk(core.NewVec2i( 1,  1))
}