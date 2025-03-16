# Tilemap

The tilemap is one of the most tricky systems in the engine. It made me go insane.

## A world of tiles

A world is composed of chunks, which are composed of tiles. The current world is `tile.ThisWorld`.

Chunks are 16x16x1 tiles and are pretty much just so your computer doesn't explode.

Tile coordinates are different from screen coordinates; (5, 5) is 5 tiles, not 5 pixels

Starry has a Z axis too. You can dig a hole if you want.

A tile is pretty tiny:

```go
type Tile struct {
	TileId    Id
	EntityRef entity.Ref
	Variation Variation
}
```

The tile ID is a random number corresponding to an actual tile with actual information (such as the texture).
The entity and variation is just for fancy tiles.

The reason tiles are tiny is so you can have like a lot of tiles without annihilating your PC

To get tiles you can use `world.GetTile()` or make new tiles with `world.NewTile()`.

There's 2 layers: the ground, which is, well the ground, and the objects, which is things on top of the ground,
which are most things.

Please note that a tile not existing could either be nil, or an air tile (id of 0)