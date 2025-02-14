#include <stdio.h>
#include <math.h>
#include "modules/graphics/graphics.h"
#include "tilemap.h"

StWorld* StWorld_new(stvec2i min_chunk, stvec2i max_chunk)
{
    StWorld* world = malloc(sizeof(StWorld));
    world->chunks = StHashMap_new(0);
    world->current_chunk = STVEC2I_ZERO;
    world->current_layer = 0;
    world->camera_pos = STVEC2_ZERO;
    world->camera_zoom = (stvec2){1, 1};

    // make the bloody chunks bloody hell mate
    for (int64 x = min_chunk.x; x < max_chunk.y; x++) {
        for (int64 y = min_chunk.y; y < max_chunk.y; y++) {
            StChunk* chunk = malloc(sizeof(StChunk));

            // i hope you dont have 89523478958924893 chunks
            char key[64];
            sprintf(key, "%li,%li", x, y);
            StHashMap_set(world->chunks, key, chunk);
        }
    }
}

void StWorld_free(StWorld* w)
{
    // free chunks
    StList* items = StHashMap_items(w->chunks);
    for (nint i = 0; i < items->length; i++) {
        free(items->items[i]);
    }
    StList_free(items);
    StHashMap_free(w->chunks);
    free(w);
}

StTile* StWorld_get_tile(StWorld* w, stvec3 pos, bool ground)
{
    // man
    stvec2i chunk_pos = {
        (int64)floor(pos.x / ST_CHUNK_DIMENSIONS),
        (int64)floor(pos.z / ST_CHUNK_DIMENSIONS)
    };

    char key[64];
    sprintf(key, "%li,%li", chunk_pos.x, chunk_pos.y);

    StChunk* chunk = StHashMap_get(w->chunks, key);
    StLayer layer = chunk->layers[(uint64)(pos.y + -ST_MIN_LAYER)];

    stvec2i offsetted = {
        pos.x - (chunk_pos.x * ST_CHUNK_DIMENSIONS),
        pos.y - (chunk_pos.y * ST_CHUNK_DIMENSIONS)
    };

    if (ground) return &(layer.ground[offsetted.x][offsetted.y]);
    else return &(layer.objects[offsetted.x][offsetted.y]);
}

void __st_render_tile__(StTile tile)
{
    StGraphics_draw_texture_ext(
        tile.textures[tile.side],
        STVEC2_ZERO,
        (stvec2){tile.textures[tile.side]->width, tile.textures[tile.side]->height},
        (stvec2){
            (tile.position.x + StWorld_current()->camera_pos.x) * 
                StWorld_current()->camera_zoom.x * tile.textures[tile.side]->width,
            (tile.position.y + StWorld_current()->camera_pos.y) * 
                StWorld_current()->camera_zoom.y * tile.textures[tile.side]->height,
        },
        (stvec2){
            tile.textures[tile.side]->width * StWorld_current()->camera_zoom.x,
            tile.textures[tile.side]->height * StWorld_current()->camera_zoom.y,
        },
        STVEC2_ZERO, 0, tile.tint
    );
}

void __st_render_chunk__(stvec2i chunk, int64 layer)
{
    char key[64];
    sprintf(key, "%li,%li", chunk.x, chunk.y);

    StChunk* chunkma = StHashMap_get(StWorld_current()->chunks, key);
    StLayer layerma = chunkma->layers[(uint64)(layer + -ST_MIN_LAYER)];

    for (nint x = 0; x < ST_CHUNK_DIMENSIONS; x++) {
        for (nint y = 0; y < ST_CHUNK_DIMENSIONS; y++) {
            StTile tile = layerma.ground[x][y];
            __st_render_tile__(tile);
        }
    }
}

void __st_update_tilemap__()
{
    // can't draw a world if there's no world
    if (StWorld_current == NULL) return;

    // TODO this will crash at the corner at the world and it's a really easy fix
    // but im already having a headache
    for (int32 x = -1; x < 2; x++) {
        for (int32 y = -1; y < 2; y++) {
            __st_render_chunk__(stvec2i_add(StWorld_current()->current_chunk, (stvec2i){x, y}),
                StWorld_current()->current_layer);
        }
    }
}

StWorld* __st_current__;

StWorld* StWorld_current()
{
    return __st_current__;
}

void StWorld_set_current(StWorld* w)
{
    __st_current__ = w;
}