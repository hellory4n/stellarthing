#ifndef ST_TILEMAP_H
#define ST_TILEMAP_H
#include "core/collections/array.hpp"
#include "core/collections/hashmap.hpp"
#include "core/math/vec2i.hpp"
#include "core/math/vec3.hpp"
#include "core/math/color.hpp"
#include "core/ref.hpp"
#include "texture.hpp"

namespace starry {

/// how down can you go
#define ST_MIN_LAYER -64

/// how up can you go
#define ST_MAX_LAYER 256

/// mate
#define ST_TOTAL_LAYERS 320

/// chunk isze
#define ST_CHUNK_SIZE 16

/// A tile-based video game, or grid-based video game, is a type of video game where the playing area consists of small square (or, much less often, rectangular, parallelogram, or hexagonal) graphic images referred to as tiles laid out in a grid. That the screen is made of such tiles is a technical distinction, and may not be obvious to people playing the game. The complete set of tiles available for use in a playing area is called a tileset. Tile-based games usually simulate a top-down, side view, or 2.5D view of the playing area, and are almost always two-dimensional. 
struct Tile {
    /// z is the layer
    Vec3 position = Vec3(0, 0, 0);
    /// el scorcho! AY CABRÓN
    Color tint = ST_COLOR_WHITE;
    /// i have 3 sides... i'm a triangle
    uint8 side = 0;
    /// if true, the tile is in fact no tile. default for tiles until you fill them with something
    bool empty = true;
    /// texture
    Ref<Texture> texture0 = {0};
    /// texture
    Ref<Texture> texture1 = {0};
    /// texture
    Ref<Texture> texture2 = {0};
    /// texture
    Ref<Texture> texture3 = {0};

    /// clang was having a stroke with a C-style array
    Ref<Texture> get_texture();
};

/// its a world of tiles... truly gives a world of possibilities HAHAHBAHAHAHHAHAAHHAAHEHOEGOHHKHRTIJOHYJIORIOGREFYH;TPHOY;IFPPIKPGPJOILKṔ;Ó[;O]-;I90;[-P89P0689;0-P69]P´[9]0]
class TileWorld {
private:
    void __draw_chunk(Vec2i offset);
public:
    /// it's a hashmap of chunk positions and an array of their layers, each with an array of tiles
    HashMap<Vec2i, Array<Array<Tile>*>*> ground;
    HashMap<Vec2i, Array<Array<Tile>*>*> objects;

    Vec2i current_chunk = Vec2i(0, 0);
    int64 current_layer = 0;

    Vec2 camera_position = Vec2(0, 0);
    Vec2 camera_scale = Vec2(1, 1);

    TileWorld(Vec2i min_chunk, Vec2i max_chunk);
    ~TileWorld();

    /// adds a tile
    Tile* add_tile(Vec3 pos, bool ground, Ref<Texture> side0, Ref<Texture> side1, Ref<Texture> side2, Ref<Texture> side3);

    /// gets a tile.
    Tile* get_tile(Vec3 pos, bool ground);

    /// seeing is an core mechanic of the hit videogame Stellarshit
    void draw();
};

}

#endif // ST_TILEMAP_H
