# Tilemap

Tilemaps are quite cool.

Tile coordinates are vector3s because the Z axis is the layer, which makes it kinda 3D.

Tile coordinates also are in number of tiles, not pixels.

There's also support for multiple worlds, "" is space.

Layers range from -128 to 512:
- -128 to -1: underground stuff
- 0: the ground
- 1 to 512: just space for more building

Tiles can have multiple sides for some reason.

To use tiles in your epic entities you can use the `Tile` class

```cs
Tile? tile;
public async void create()
{
    tile = new(
        await Starry.load<Sprite>("left"),
        await Starry.load<Sprite>("right"),
        await Starry.load<Sprite>("top"),
        await Starry.load<Sprite>("bottom")) {
        position = (0, 0, 0),
    };
}
```

You can also use [animations](animation.md) with `Tile`

See the `Tilemap` class.