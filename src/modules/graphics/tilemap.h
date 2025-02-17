#pragma once
#include "core/vectors.h"
#include "core/math/stcolor.h"
#include "core/collections/sthashmap.h"
#include "texture.h"

/// tile
typedef struct {
    /// y is up
    stvec3 position;
    /// changes the color of the tile. make it white to not change the color
    stcolor tint;
    /// textures. each element is one of the sides. order doesn't really matter
    StTexture* textures[4];
    /// side, from 0 to 3
    uint8 side;
} StTile;

#ifndef ST_MIN_LAYER
/// how down can you go
#define ST_MIN_LAYER -64
#endif

#ifndef ST_MAX_LAYER
/// how up can you go
#define ST_MAX_LAYER 256
#endif

#ifndef ST_TOTAL_LAYERS
// layer
#define ST_TOTAL_LAYERS 320
#endif

#ifndef ST_WORLD_DIMENSIONS
/// can't be bothered to make proper chunking for now
#define ST_WORLD_DIMENSIONS 250
#endif

typedef struct {
    StTile ground[ST_WORLD_DIMENSIONS][ST_TOTAL_LAYERS][ST_WORLD_DIMENSIONS];
    StTile objects[ST_WORLD_DIMENSIONS][ST_TOTAL_LAYERS][ST_WORLD_DIMENSIONS];

    stvec2i current_chunk;
    int64 current_layer;

    stvec2 camera_pos;
    /// it's a multiplier
    stvec2 camera_zoom;
} StWorld;

/// makes a world :)
StWorld* StWorld_new();

/// I WANT TO BREAK FREE
void StWorld_free(StWorld* w);

/// tile
StTile* StWorld_get_tile(StWorld* w, stvec3 pos, bool ground);

/// makes a new tile :)
StTile* StWorld_new_tile(StWorld* w, stvec3 pos, bool ground, StTexture* side0, StTexture* side1,
    StTexture* side2, StTexture* side3);

/// returns the current world
StWorld* StWorld_current();

/// sets the current world
void StWorld_set_current(StWorld* w);

/// draws a world
void StWorld_draw(StWorld* w);