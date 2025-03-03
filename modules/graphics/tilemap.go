package graphics

// how down can you go
const MinLayer int = -16

// how up can you go
const MaxLayer int = 48

// mate
const TotalLayers int = 64

// chunk size (they're square)
const ChunkSize int = 16

type Tile struct {
	TileId uint32
	EntityId uint32
}

type TileWorld struct {
	Mate [9][64][16][16]Tile
}

// it's a tile. use with TileWorld
/*type Tile struct {
	// z is the layer
	Position core.Vec3
	// el scorcho! AY CABRÓN
	Tint core.Color
	// i have 3 sides... i'm a triangle
	Side uint8
	// if false, the tile is in fact no tile. useful for, for example, a space world, where it's mostly nothing
	Exists bool
	// textures. order doesn't really matter
	Textures [4]Texture
}

// as the name implies, it's a world of tiles... truly gives a world of possibilities HAHAHBAHAHAHHAHAAHHAAHEHOEGOHHKHRTIJOHYJIORIOGREFYH;TPHOY;IFPPIKPGPJOILKṔ;Ó[;O]-;I90;[-P89P0689;0-P69]P´[9]0]
type TileWorld struct {
	// the top left corner of the world
	StartPos core.Vec2
	// the bottom right corner of the world
	EndPos core.Vec2
	// camera position :)
	CameraPos core.Vec3
	// camera scale. it's a multiplier so 1, 1 is the original size
	CameraScale core.Vec2
	// indexed like [z][y][x] :)
	ground [][][]Tile
	// indexed like [z][y][x] :)
	objects [][][]Tile
}

// current world
var CurrentWorld *TileWorld

// makes a new world. the startPos and endPos are the top left and bottom right corners of the world, respectively
func NewTileWorld(worldSize core.Vec2i) *TileWorld {
	var world *TileWorld = new(TileWorld)
	world.StartPos = worldSize.ToVec2().Sdiv(2).Neg()
	world.EndPos = worldSize.ToVec2().Sdiv(2)
	world.CameraPos = core.NewVec3(0, 0, 0)
	world.CameraScale = core.NewVec2(1, 1)
	
	// i should
	world.ground = make([][][]Tile, TotalLayers)
	for z := range world.ground {
		world.ground[z] = make([][]Tile, worldSize.Y)
		for y := range world.ground[z] {
			world.ground[z][y] = make([]Tile, worldSize.X)
		}
	}

	world.objects = make([][][]Tile, TotalLayers)
	for z := range world.objects {
		world.objects[z] = make([][]Tile, worldSize.Y)
		for y := range world.objects[z] {
			world.objects[z][y] = make([]Tile, worldSize.X)
		}
	}

	return world
}

// as the name implies it transforms from tile positions to global positions
func (t *TileWorld) TransformToGlobal(tilePos core.Vec2, tileSize core.Vec2) core.Vec2 {
	return tilePos.Add(core.NewVec2(t.CameraPos.X, t.CameraPos.Y)).Mul(t.CameraScale).Mul(tileSize)
}

// gets a tile from a position
func (t *TileWorld) GetTile(pos core.Vec3, ground bool) *Tile {
	idx := core.NewVec3i(
		// StartPos is supposed to be negative so 0, 0 is on the center :)
		int64(math.Round(pos.X) + -t.StartPos.X),
		int64(math.Round(pos.Y) + -t.StartPos.Y),
		int64(math.Round(pos.Z)) + -int64(MinLayer),
	)

	var tile Tile
	if ground {
		tile = t.ground[idx.Z][idx.Y][idx.X]
	} else {
		tile = t.objects[idx.Z][idx.Y][idx.X]
	}

	return &tile
}

// makes a new tile with sensible settings :)
func (t *TileWorld) NewTile(pos core.Vec3, ground bool, side0 Texture, side1 Texture, side2 Texture, side3 Texture) *Tile {
	tile := t.GetTile(pos, ground)
	tile.Exists = true
	tile.Position = pos
	tile.Tint = core.ColorWhite
	tile.Textures[0] = side0
	tile.Textures[1] = side1
	tile.Textures[2] = side2
	tile.Textures[3] = side3
	return tile
}

// renders the world. usually quite useful unless you're blind
func (t *TileWorld) Draw() {
	for y := t.StartPos.Y; y < t.EndPos.Y; y++ {
		for x := t.StartPos.X; x < t.EndPos.X; x++ {
			// ground tiles
			var tile *Tile = t.GetTile(core.NewVec3(x, y, t.CameraPos.Z), false)

			DrawTextureExt(
				tile.Textures[tile.Side],
				core.NewVec2(0, 0),
				tile.Textures[tile.Side].Size().ToVec2(),
				t.TransformToGlobal(
					core.NewVec2(tile.Position.X, tile.Position.Y), tile.Textures[tile.Side].Size().ToVec2(),
				),
				tile.Textures[tile.Side].Size().ToVec2().Mul(t.CameraScale),
				core.NewVec2(0, 0),
				0,
				core.ColorWhite,
			)

			// object tiles
			var til *Tile = t.GetTile(core.NewVec3(x, y, t.CameraPos.Z), true)

			DrawTextureExt(
				til.Textures[til.Side],
				core.NewVec2(0, 0),
				til.Textures[til.Side].Size().ToVec2(),
				t.TransformToGlobal(
					core.NewVec2(til.Position.X, til.Position.Y), til.Textures[til.Side].Size().ToVec2(),
				),
				til.Textures[til.Side].Size().ToVec2().Mul(t.CameraScale),
				core.NewVec2(0, 0),
				0,
				core.ColorWhite,
			)
		}
	}
}*/