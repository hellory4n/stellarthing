#include <stdio.h>
#include "tilemap.h"

StWorld* StWorld_new(stvec2i min_chunk, stvec2i max_chunk)
{
    StWorld* world = malloc(sizeof(StWorld));
    world->chunks = StHashMap_new(0);
    world->current_chunk = (stvec2i){0, 0};
    world->current_layer = 0;

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

void StWorld_free(StWorld* w);

StTile* StWorld_get_tile(StWorld* w, stvec3 pos);

void __st_update_tilemaps__();