#include <stdio.h>
#include <math.h>
#include "modules/graphics/graphics.h"
#include "tilemap.h"

StWorld* __st_current__;

StWorld* StWorld_new(stvec2i min_chunk, stvec2i max_chunk)
{
    StWorld* world = malloc(sizeof(StWorld));
    world->current_chunk = STVEC2I_ZERO;
    world->current_layer = 0;
    world->camera_pos = STVEC2_ZERO;
    world->camera_zoom = (stvec2){1, 1};

    printf("[WORLD] New world created\n");
    return world;
}

void StWorld_free(StWorld* w)
{
    printf("[WORLD] World deleted\n");
    // I WANT TO BREAK FREE
    free(w);
}

StTile* StWorld_get_tile(StWorld* w, stvec3 pos, bool ground)
{
    if (ground) {
        // MANIACAL
        return &(w->ground[(int64)floor(pos.x)][(int64)floor(pos.y + (-ST_MIN_LAYER))][(int64)floor(pos.z)]);
    }
    else {
        return &(w->objects[(int64)floor(pos.x)][(int64)floor(pos.y + (-ST_MIN_LAYER))][(int64)floor(pos.z)]);
    }
}

StTile* StWorld_new_tile(StWorld* w, stvec3 pos, bool ground, StTexture* side0, StTexture* side1,
    StTexture* side2, StTexture* side3)
{
    StTile* letilee = StWorld_get_tile(w, pos, ground);
    letilee->position = pos;
    letilee->side = 0;
    letilee->tint = ST_WHITE;
    letilee->textures[0] = side0;
    letilee->textures[1] = side1;
    letilee->textures[2] = side2;
    letilee->textures[3] = side3;
    return letilee;
}

void __st_render_tile__(StWorld* world, StTile tile)
{
    // lamo
    if (tile.textures[0] == NULL) return;

    StGraphics_draw_texture_ext(
        tile.textures[tile.side],
        STVEC2_ZERO,
        (stvec2){tile.textures[tile.side]->width, tile.textures[tile.side]->height},
        (stvec2){
            (tile.position.x + world->camera_pos.x) * world->camera_zoom.x * tile.textures[tile.side]->width,
            (tile.position.z + world->camera_pos.y) * world->camera_zoom.y * tile.textures[tile.side]->height,
        },
        (stvec2){
            tile.textures[tile.side]->width  * world->camera_zoom.x,
            tile.textures[tile.side]->height * world->camera_zoom.y,
        },
        STVEC2_ZERO, 0, tile.tint
    );
}

void StWorld_draw(StWorld* w)
{
    for (int64 x = 0; x < ST_WORLD_DIMENSIONS; x++) {
        for (int64 z = 0; z < ST_WORLD_DIMENSIONS; z++) {
            // man
            __st_render_tile__(w, *StWorld_get_tile(__st_current__, (stvec3){x, __st_current__->current_layer, z}, true));
            __st_render_tile__(w, *StWorld_get_tile(__st_current__, (stvec3){x, __st_current__->current_layer, z}, false));
        }
    }
}

StWorld* StWorld_current()
{
    return __st_current__;
}

void StWorld_set_current(StWorld* w)
{
    __st_current__ = w;
}