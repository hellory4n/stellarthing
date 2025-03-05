package graphics

import (
	// "fmt"
	"maps"
	"math"
	"math/rand"

	"github.com/hellory4n/stellarthing/core"
	"github.com/hellory4n/stellarthing/modules/entities"
)

// how down can you go
const MinLayer int64 = -16

// how up can you go
const MaxLayer int64 = 48

// mate
const TotalLayers int64 = 64

// chunk size (they're square)
const ChunkSize int64 = 16

// optimized tile. for actual data use TileData
type Tile struct {
	TileId TileId
	EntityRef entities.EntityRef
	Variation VariationId
}

// as the name implies, it gets the data
func (t *Tile) GetData() *TileData {
	lol := Tiles[t.TileId][t.Variation]
	return &lol
}

// world of tiles :D
type TileWorld struct {
	Seed int64
	randGen *rand.Rand
	// set with SetCameraPosition :)
	CameraPosition core.Vec3
	// the top left corner
	StartPos core.Vec2i
	// the bottom right corner
	EndPos core.Vec2i
	LoadedGroundTiles map[core.Vec3i]Tile
	LoadedObjectTiles map[core.Vec3i]Tile
	LoadedChunks []core.Vec3i
}

// current world.
var CurrentWorld *TileWorld

// makes a new world. the startPos is the top left corner and the endPos is the bottom right corner.
func NewTileWorld(startPos core.Vec2i, endPos core.Vec2i, seed int64) *TileWorld {
	tilhjjh := &TileWorld{}
	tilhjjh.StartPos = startPos
	tilhjjh.EndPos = endPos
	tilhjjh.Seed = seed
	tilhjjh.randGen = rand.New(rand.NewSource(tilhjjh.Seed))
	tilhjjh.LoadedGroundTiles = make(map[core.Vec3i]Tile)
	tilhjjh.LoadedObjectTiles = make(map[core.Vec3i]Tile)

	// load some chunks :)
	tilhjjh.SetCameraPosition(core.NewVec3(0, 0, 0))

	return tilhjjh
}

// sets the camera position and loads chunks
func (t *TileWorld) SetCameraPosition(pos core.Vec3) {
	// so i can use early returns :)
	defer func() { t.CameraPosition = pos }()

	chunkX := int64(math.Floor(pos.X)) / ChunkSize
	chunkY := int64(math.Floor(pos.Y)) / ChunkSize
	chunkPos := core.NewVec3i(chunkX, chunkY, int64(pos.Z)).Sdiv(ChunkSize)

	// do we even have to load it at all?
	_, hasChunk := t.LoadedGroundTiles[chunkPos.Smul(ChunkSize)]
	if hasChunk {
		return
	}

	// TODO check if it's on the save

	// if it's not on the save we generate it
	newGround, newObjects := GenerateChunk(t.randGen, chunkPos)
	maps.Copy(t.LoadedGroundTiles, newGround)
	maps.Copy(t.LoadedObjectTiles, newObjects)
	t.LoadedChunks = append(t.LoadedChunks, chunkPos)
}

// as the name implies, it gets a tile
func (t *TileWorld) GetTile(pos core.Vec3i, ground bool) *Tile {
	var letile Tile
	if ground {
		letile = t.LoadedGroundTiles[pos]
	} else {
		letile = t.LoadedObjectTiles[pos]
	}
	return &letile
}

// it draws the world. no shit.
func (t *TileWorld) Draw() {
	// we draw the neighbors of the current chunk so it doesn't look funny
	// when crossing chunk borders
	// fmt.Println("MATE")
	renderAreaStartX := int64(math.Floor(t.CameraPosition.X - float64(ChunkSize)))
	// fmt.Println(renderAreaStartX)
	renderAreaStartY := int64(math.Floor(t.CameraPosition.Y - float64(ChunkSize)))
	// fmt.Println(renderAreaStartY)
	renderAreaEndX := int64(math.Floor(t.CameraPosition.X + float64(ChunkSize)))
	// fmt.Println(renderAreaEndX)
	renderAreaEndY := int64(math.Floor(t.CameraPosition.Y + float64(ChunkSize)))
	// fmt.Println(renderAreaEndY)

	for x := renderAreaStartX; x < renderAreaEndX; x++ {
		for y := renderAreaStartY; y < renderAreaEndY; y++ {
			// do you think the human mind was a mistake
			tile := t.LoadedObjectTiles[core.NewVec3i(x, y, int64(t.CameraPosition.Z))]
			data := Tiles[tile.TileId][tile.Variation]
			// YOU SEE TEXTURES ARE CACHED SO ITS NOT TOO OUTRAGEOUS TO PUT SOMETHING IN A FUNCTION
			// RAN EVERY FRAME
			texture := LoadTexture(data.Texture)

			var pos core.Vec2
			if data.UsingCustomPos {
				pos = core.NewVec2(data.Position.X, data.Position.Y).Mul(texture.Size().ToVec2())
			} else {
				pos = core.NewVec2(float64(x), float64(y)).Mul(texture.Size().ToVec2())
			}

			DrawTexture(texture, pos, 0, data.Tint)

			// do you think the human mind was a mistake
			til := t.LoadedObjectTiles[core.NewVec3i(x, y, int64(t.CameraPosition.Z))]
			dat := Tiles[til.TileId][til.Variation]
			// YOU SEE TEXTURES ARE CACHED SO ITS NOT TOO OUTRAGEOUS TO PUT SOMETHING IN A FUNCTION
			// RAN EVERY FRAME
			textur := LoadTexture(dat.Texture)

			var po core.Vec2
			if dat.UsingCustomPos {
				po = core.NewVec2(dat.Position.X, dat.Position.Y).Mul(textur.Size().ToVec2())
			} else {
				po = core.NewVec2(float64(x), float64(y)).Mul(textur.Size().ToVec2())
			}

			DrawTexture(textur, po, 0, dat.Tint)
		}
	}
}