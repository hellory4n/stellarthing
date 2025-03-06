package graphics

import (
	"fmt"
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
	return Tiles[t.TileId][t.Variation]
}

func (t *Tile) String() string {
	return fmt.Sprintf("%v (variation %v, owned by %v)", TileNames[t.TileId], t.Variation, t.EntityRef)
}

// world of tiles :D
type TileWorld struct {
	Seed int64
	randGen *rand.Rand
	// set with SetCameraPosition :)
	CameraPosition core.Vec3
	// mate
	CameraOffset core.Vec2
	// the top left corner
	StartPos core.Vec2i
	// the bottom right corner
	EndPos core.Vec2i
	LoadedGroundTiles map[core.Vec3i]*Tile
	LoadedObjectTiles map[core.Vec3i]*Tile
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
	tilhjjh.LoadedGroundTiles = make(map[core.Vec3i]*Tile)
	tilhjjh.LoadedObjectTiles = make(map[core.Vec3i]*Tile)
	// TODO make shit render at a specific resolution then scale it to fit the actual resolution
	tilhjjh.CameraOffset = core.NewVec2(1366, 768).Sdiv(2)

	fmt.Println("[TILEMAP] Created new world")

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
	fmt.Printf("[TILEMAP] Generating chunk at %v\n", chunkPos)
	newGround, newObjects := GenerateChunk(t.randGen, chunkPos)

	// copy crap
	for k, v := range newGround {
		t.LoadedGroundTiles[k] = v
	}
	for k, v := range newObjects {
		t.LoadedObjectTiles[k] = v
	}
	t.LoadedChunks = append(t.LoadedChunks, chunkPos)
}

// as the name implies, it gets a tile
func (t *TileWorld) GetTile(pos core.Vec3i, ground bool) *Tile {
	if ground {
		return t.LoadedGroundTiles[pos]
	} else {
		return t.LoadedObjectTiles[pos]
	}
}

// as the name implies, it makes a new tile. if the variation doesn't exist, it's gonna copy the
// default variation too
func (t *TileWorld) NewTile(pos core.Vec3i, ground bool, tileId TileId, entity entities.EntityRef,
variation VariationId) *Tile {
	var letile *Tile = &Tile{
		TileId: tileId,
		EntityRef: entity,
		Variation: variation,
	}

	_, variationExists := Tiles[tileId][variation]
	if !variationExists {
		Tiles[tileId][variation] = Tiles[tileId][0]
	}

	if ground {
		t.LoadedGroundTiles[pos] = letile
	} else {
		t.LoadedObjectTiles[pos] = letile
	}

	return letile
}

func (t *TileWorld) drawTile(pos core.Vec2i, ground bool) {
	// grod ng tiles
	tile := t.GetTile(core.NewVec3i(pos.X, pos.Y, int64(t.CameraPosition.Z)), ground)
	if tile == nil {
		return
	}
	data := tile.GetData()
	// YOU SEE TEXTURES ARE CACHED SO ITS NOT TOO OUTRAGEOUS TO PUT SOMETHING IN A FUNCTION
	// RAN EVERY FRAME
	texture := LoadTexture(data.Texture)

	var pospos core.Vec2
	if data.UsingCustomPos {
		//((tile.position.as2d.sub(camPosition)).mul(Starry.settings.tileSize)).add(camOffset)
		// im losing my mind
		// im going insane
		// im watching my life go down the drain
		pospos = core.NewVec2(
			((data.Position.X - t.CameraPosition.X) * texture.Size().ToVec2().X) + t.CameraOffset.X,
			((data.Position.Y - t.CameraPosition.Y) * texture.Size().ToVec2().Y) + t.CameraOffset.Y,
		)
	} else {
		pospos = core.NewVec2(
			((float64(pos.X) - t.CameraPosition.X) * texture.Size().ToVec2().X) + t.CameraOffset.X,
			((float64(pos.Y) - t.CameraPosition.Y) * texture.Size().ToVec2().Y) + t.CameraOffset.Y,
		)
	}

	DrawTexture(texture, pospos, 0, data.Tint)
}

// it draws the world. no shit.
func (t *TileWorld) Draw() {
	// we draw the neighbors of the current chunk so it doesn't look funny
	// when crossing chunk borders
	renderAreaStartX := int64(math.Floor(t.CameraPosition.X - float64(ChunkSize)))
	renderAreaStartY := int64(math.Floor(t.CameraPosition.Y - float64(ChunkSize)))
	renderAreaEndX := int64(math.Floor(t.CameraPosition.X + float64(ChunkSize)))
	renderAreaEndY := int64(math.Floor(t.CameraPosition.Y + float64(ChunkSize)))

	for x := renderAreaStartX; x < renderAreaEndX; x++ {
		for y := renderAreaStartY; y < renderAreaEndY; y++ {
			t.drawTile(core.NewVec2i(x, y), true)
		}
	}
	for x := renderAreaStartX; x < renderAreaEndX; x++ {
		for y := renderAreaStartY; y < renderAreaEndY; y++ {
			t.drawTile(core.NewVec2i(x, y), false)
		}
	}
}