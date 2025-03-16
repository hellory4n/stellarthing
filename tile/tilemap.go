package tile

import (
	"fmt"
	"math"
	"math/rand"

	"github.com/hellory4n/stellarthing/core"
	"github.com/hellory4n/stellarthing/entity"
	"github.com/hellory4n/stellarthing/platform/graphics"
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
	TileId    Id
	EntityRef entity.Ref
	Variation Variation
}

// as the name implies, it gets the data
func (t *Tile) GetData() *TileData {
	return Tiles[t.TileId][t.Variation]
}

func (t *Tile) String() string {
	if t.Variation == 0 && t.EntityRef == 0 {
		return TileNames[t.TileId]
	} else {
		return fmt.Sprintf("%v (variation %v, owned by %v)", TileNames[t.TileId], t.Variation, t.EntityRef)
	}
}

// world of tiles :D
type World struct {
	Seed    int64
	randGen *rand.Rand
	// set with SetCameraPosition :)
	CameraPosition core.Vec3
	// mate
	CameraOffset core.Vec2
	// multiplier. you can zoom in on things.
	CameraScale core.Vec2
	// the top left corner
	StartPos core.Vec2i
	// the bottom right corner
	EndPos core.Vec2i
	// the keys are vec3is, i used a string so it works in json
	LoadedGroundTiles map[core.Vec3i]*Tile
	LoadedObjectTiles map[core.Vec3i]*Tile
	LoadedChunks      []core.Vec3i
	// this sucks
	theyMightBeMoving []*Tile
}

// current world.
var ThisWorld *World

// makes a new world. the startPos is the top left corner and the endPos is the bottom right corner.
func NewWorld(startPos core.Vec2i, endPos core.Vec2i, seed int64) *World {
	tilhjjh := &World{}
	tilhjjh.StartPos = startPos
	tilhjjh.EndPos = endPos
	tilhjjh.Seed = seed
	tilhjjh.randGen = rand.New(rand.NewSource(tilhjjh.Seed))
	tilhjjh.LoadedGroundTiles = make(map[core.Vec3i]*Tile)
	tilhjjh.LoadedObjectTiles = make(map[core.Vec3i]*Tile)
	tilhjjh.CameraOffset = core.RenderSize.Sdiv(2).ToVec2()
	tilhjjh.CameraScale = core.Vec2{1, 1}
	fmt.Println("[TILEMAP] Created new world")

	// load some chunks :)
	tilhjjh.SetCameraPosition(core.Vec3{-float64(ChunkSize), 0, 0})
	tilhjjh.SetCameraPosition(core.Vec3{float64(ChunkSize), 0, 0})
	tilhjjh.SetCameraPosition(core.Vec3{0, float64(ChunkSize), 0})
	tilhjjh.SetCameraPosition(core.Vec3{0, -float64(ChunkSize), 0})
	tilhjjh.SetCameraPosition(core.Vec3{float64(ChunkSize), float64(ChunkSize), 0})
	tilhjjh.SetCameraPosition(core.Vec3{-float64(ChunkSize), -float64(ChunkSize), 0})
	tilhjjh.SetCameraPosition(core.Vec3{0, 0, 0})

	return tilhjjh
}

// sets the camera position and loads chunks
func (w *World) SetCameraPosition(pos core.Vec3) {
	// so i can use early returns :)
	defer func() { w.CameraPosition = pos }()

	chunkX := int64(pos.X / float64(ChunkSize))
	chunkY := int64(pos.Y / float64(ChunkSize))
	chunkPos := core.Vec3i{chunkX, chunkY, int64(pos.Z)}

	// do we even have to load it at all?
	_, hasChunk := w.LoadedGroundTiles[core.Vec3i{int64(pos.X), int64(pos.Y), int64(pos.Z)}]
	if hasChunk {
		return
	}

	// if it's not on the save we generate it
	// generate multiple chunks fuck it
	man := func(offset core.Vec3i) {
		fmt.Printf("[TILEMAP] Generating chunk at %v\n", chunkPos.Add(offset))
		newGround, newObjects := GenerateChunk(w.randGen, chunkPos.Add(offset))

		// copy crap
		for k, v := range newGround {
			w.LoadedGroundTiles[k] = v
		}
		for k, v := range newObjects {
			w.LoadedObjectTiles[k] = v
		}
		w.LoadedChunks = append(w.LoadedChunks, chunkPos.Add(offset))
	}
	man(core.Vec3i{0, 0, 0})
	man(core.Vec3i{-1, -1, 0})
	man(core.Vec3i{0, -1, 0})
	man(core.Vec3i{1, 0, 0})
	man(core.Vec3i{-1, 0, 0})
	man(core.Vec3i{0, 1, 0})
	man(core.Vec3i{-1, 1, 0})
	man(core.Vec3i{0, 1, 0})
	man(core.Vec3i{1, 1, 0})
}

// as the name implies, it gets a tile. returns nil if it's not there.
func (t *World) GetTile(pos core.Vec3i, ground bool) *Tile {
	if ground {
		return t.LoadedGroundTiles[pos]
	} else {
		return t.LoadedObjectTiles[pos]
	}
}

// as the name implies, it makes a new tile. if the variation doesn't exist, it's gonna copy the
// default variation too
func (w *World) NewTile(pos core.Vec3i, ground bool, tile Id, ent entity.Ref,
	variation Variation) *Tile {
	var letile *Tile = &Tile{
		TileId:    tile,
		EntityRef: ent,
		Variation: variation,
	}

	_, variationExists := Tiles[tile][variation]
	if !variationExists {
		Tiles[tile][variation] = Tiles[tile][0]
	}

	if ground {
		w.LoadedGroundTiles[pos] = letile
	} else {
		w.LoadedObjectTiles[pos] = letile
	}

	// man
	if ent != 0 {
		w.theyMightBeMoving = append(w.theyMightBeMoving, letile)
	}

	return letile
}

func (w *World) drawTile(pos core.Vec2i, ground bool) {
	// grod ng tiles
	tile := w.GetTile(core.Vec3i{pos.X, pos.Y, int64(w.CameraPosition.Z)}, ground)
	if tile == nil {
		return
	}
	data := tile.GetData()
	// YOU SEE TEXTURES ARE CACHED SO ITS NOT TOO OUTRAGEOUS TO PUT SOMETHING IN A FUNCTION
	// RAN EVERY FRAME
	texture := graphics.LoadTexture(data.Texture)

	var pospos core.Vec2
	if data.UsingCustomPos {
		// im losing my mind
		// im going insane
		// im watching my life go down the drain
		pospos = core.Vec2{
			((data.Position.X - w.CameraPosition.X) * (texture.Size().ToVec2().X * w.CameraScale.X)) + w.CameraOffset.X,
			((data.Position.Y - w.CameraPosition.Y) * (texture.Size().ToVec2().Y * w.CameraScale.Y)) + w.CameraOffset.Y,
		}
	} else {
		pospos = core.Vec2{
			((float64(pos.X) - w.CameraPosition.X) * (texture.Size().ToVec2().X * w.CameraScale.X)) + w.CameraOffset.X,
			((float64(pos.Y) - w.CameraPosition.Y) * (texture.Size().ToVec2().Y * w.CameraScale.Y)) + w.CameraOffset.Y,
		}
	}

	graphics.DrawTextureExt(
		texture,
		core.Vec2{0, 0},
		texture.Size().ToVec2(),
		pospos,
		texture.Size().ToVec2().Mul(w.CameraScale),
		core.Vec2{0, 0},
		0, data.Tint,
	)
}

// it draws the world. no shit.
func (w *World) Draw() {
	// stop busting
	var renderAreaStartX int64
	var renderAreaStartY int64
	var renderAreaEndX int64
	var renderAreaEndY int64

	// we draw the neighbors of the current chunk so it doesn't look funny when crossing chunk borders
	// you can see more if you're really zoomed out
	// * 1.5 on the x axis because screens are wide
	if w.CameraScale.Lt(core.Vec2{0.9, 0.9}) {
		// When zoomed out, extend the render area by a factor of 1/scale,
		// plus an extra 1.5 multiplier on the x axis for wider screens.
		renderAreaStartX = int64(math.Floor(w.CameraPosition.X - float64(ChunkSize)*(1.5/w.CameraScale.X)))
		renderAreaStartY = int64(math.Floor(w.CameraPosition.Y - float64(ChunkSize)*(1.0/w.CameraScale.Y)))
		renderAreaEndX = int64(math.Floor(w.CameraPosition.X + float64(ChunkSize)*(1.5/w.CameraScale.X)))
		renderAreaEndY = int64(math.Floor(w.CameraPosition.Y + float64(ChunkSize)*(1.0/w.CameraScale.Y)))
	} else {
		// At normal zoom, show just one chunk size around the camera.
		renderAreaStartX = int64(math.Floor(w.CameraPosition.X - float64(ChunkSize)))
		renderAreaStartY = int64(math.Floor(w.CameraPosition.Y - float64(ChunkSize)))
		renderAreaEndX = int64(math.Floor(w.CameraPosition.X + float64(ChunkSize)))
		renderAreaEndY = int64(math.Floor(w.CameraPosition.Y + float64(ChunkSize)))
	}

	for x := renderAreaStartX; x < renderAreaEndX; x++ {
		for y := renderAreaStartY; y < renderAreaEndY; y++ {
			w.drawTile(core.Vec2i{x, y}, true)
		}
	}

	for x := renderAreaStartX; x < renderAreaEndX; x++ {
		for y := renderAreaStartY; y < renderAreaEndY; y++ {
			w.drawTile(core.Vec2i{x, y}, false)
		}
	}

	for _, tile := range w.theyMightBeMoving {
		// AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
		if tile == nil {
			return
		}
		data := tile.GetData()
		// YOU SEE TEXTURES ARE CACHED SO ITS NOT TOO OUTRAGEOUS TO PUT SOMETHING IN A FUNCTION
		// RAN EVERY FRAME
		texture := graphics.LoadTexture(data.Texture)

		var pospos core.Vec2
		if data.UsingCustomPos {
			// im losing my mind
			// im going insane
			// im watching my life go down the drain
			pospos = core.Vec2{
				((data.Position.X - w.CameraPosition.X) * (texture.Size().ToVec2().X * w.CameraScale.X)) + w.CameraOffset.X,
				((data.Position.Y - w.CameraPosition.Y) * (texture.Size().ToVec2().Y * w.CameraScale.Y)) + w.CameraOffset.Y,
			}
		} else {
			continue
		}

		graphics.DrawTextureExt(
			texture,
			core.Vec2{0, 0},
			texture.Size().ToVec2(),
			pospos,
			texture.Size().ToVec2().Mul(w.CameraScale),
			core.Vec2{0, 0},
			0, data.Tint,
		)
	}
}

// gets a tile position from screen positions
func (w *World) ScreenToTile(pos core.Vec2, textureSize core.Vec2i) core.Vec3i {
	return core.Vec3i{
		int64(math.Floor(((pos.X - w.CameraOffset.X) / (textureSize.ToVec2().X * w.CameraScale.X)) + w.CameraPosition.X)),
		int64(math.Floor(((pos.Y - w.CameraOffset.Y) / (textureSize.ToVec2().Y * w.CameraScale.Y)) + w.CameraPosition.Y)),
		int64(w.CameraPosition.Z),
	}
}

// gets a screen position from tile positions
func (w *World) TileToScreen(pos core.Vec3i, textureSize core.Vec2i) core.Vec2 {
	return core.Vec2{
		((float64(pos.X) - w.CameraPosition.X) * (textureSize.ToVec2().X * w.CameraScale.X)) + w.CameraOffset.X,
		((float64(pos.Y) - w.CameraPosition.Y) * (textureSize.ToVec2().Y * w.CameraScale.Y)) + w.CameraOffset.Y,
	}
}
