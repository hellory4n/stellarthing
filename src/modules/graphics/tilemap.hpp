#ifndef ST_TILEMAP_H
#define ST_TILEMAP_H
#include "core/vectors.hpp"
#include "core/math/color.hpp"
#include "core/collections/list.hpp"
#include "texture.hpp"

namespace starry {

/// how down can you go
#define ST_MIN_LAYER -64

/// how up can you go
#define ST_MAX_LAYER 256

/// mate
#define ST_TOTAL_LAYERS 320

/// lmao
#define ST_WORLD_SIZE 512

/// chunk isze
#define ST_CHUNK_SIZE 16

/// Tiles are usually thin, square or rectangular coverings manufactured from hard-wearing material such as ceramic, stone, metal, baked clay, or even glass. They are generally fixed in place in an array to cover roofs, floors, walls, edges, or other objects such as tabletops. Alternatively, tile can sometimes refer to similar units made from lightweight materials such as perlite, wood, and mineral wool, typically used for wall and ceiling applications. In another sense, a tile is a construction tile or similar object, such as rectangular counters used in playing games (see tile-based game). The word is derived from the French word tuile, which is, in turn, from the Latin word tegula, meaning a roof tile composed of fired clay.
struct Tile {
    /// z is the layer
    vec3 position = vec3(0, 0, 0);
    /// el scorcho! AY CABRÓN
    color tint = ST_COLOR_WHITE;
    /// i have 3 sides... i'm a triangle
    uint8 side = 0;
    /// textures. order doesn't really matter
    Texture* textures[4];

    Tile() {}
};

/// its a world of tiles... truly gives a world of possibilities HAHAHBAHAHAHHAHAAHHAAHEHOEGOHHKHRTIJOHYJIORIOGREFYH;TPHOY;IFPPIKPGPJOILKṔ;Ó[;O]-;I90;[-P89P0689;0-P69]P´[9]0]
class TileWorld {
private:
    void __draw_chunk(vec2i offset);
public:
    // can't be bothered to make proper chunking for now
    Tile ground[ST_WORLD_SIZE][ST_WORLD_SIZE][ST_TOTAL_LAYERS];
    Tile objects[ST_WORLD_SIZE][ST_WORLD_SIZE][ST_TOTAL_LAYERS];

    vec2i current_chunk = vec2i(0, 0);
    int64 current_layer = 0;

    vec2 camera_position = vec2(0, 0);
    vec2 camera_scale = vec2(1, 1);

    TileWorld();
    ~TileWorld();

    /// gets a tile.
    Tile* get_tile(vec3 pos, bool ground);

    /// seeing is an core mechanic of the hit videogame Stellarshit
    void draw();
};

}

#endif // ST_TILEMAP_H
