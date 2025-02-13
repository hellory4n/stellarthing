#pragma once
#include "core/vectors.h"
#include "core/math/stcolor.h"
#include "core/collections/sthashmap.h"
#include "texture.h"

/// tile
typedef struct {
    /// y is up
    stvec2 position;
    /// changes the color of the tile. make it white to not change the color
    stcolor tint;
    /// textures. each element is one of the sides. order doesn't really matter
    StTexture* textures[4];
    /// the world the tile is on. usually a 4 character base64 string (5 with the null character`)
    const char world[5];
    /// side, from 0 to 3
    uint8 side;
} StTile;

#ifndef ST_MIN_LAYER
/// how down can you go
#define ST_MIN_LAYER -128
#endif

#ifndef ST_MAX_LAYER
/// how up can you go
#define ST_MAX_LAYER 512
#endif

#ifndef ST_TOTAL_LAYERS
// layer
#define ST_TOTAL_LAYERS 640
#endif

#ifndef ST_CHUNK_DIMENSIONS
/// dimensions of the chunks (they're square)
#define ST_CHUNK_DIMENSIONS 32
#endif

/// man
typedef struct {
    StTile* ground[ST_CHUNK_DIMENSIONS][ST_CHUNK_DIMENSIONS];
    StTile* objects[ST_CHUNK_DIMENSIONS][ST_CHUNK_DIMENSIONS];
} StLayer;

typedef struct {
    StLayer layers[ST_TOTAL_LAYERS];
} StChunk;

typedef struct {
    /// key is stvec2i, value is StChunk*
    StHashMap* chunks;
    stvec2i current_chunk;
    int32 current_layer;
} StWorld;

/// current world :)
StWorld* StTilemap_current_world;

/// makes a world :)
StWorld* StWorld_new(stvec2i min_chunk, stvec2i max_chunk);

/// I WANT TO BREAK FREE
void StWorld_free(StWorld* w);

/// tile
StTile* StWorld_get_tile(StWorld* w, stvec3 pos);

void __st_update_tilemaps__();