#include <stdio.h>
#include <raylib.h>
#include "core/collections/sthashmap.h"
#include "texture.h"

StHashMap* __st_textures__;

void __st_init_textures__()
{
    __st_textures__ = StHashMap_new(0);
}

void __st_free_textures__()
{
    // free items in the hashmap
    StList* items = StHashMap_items(__st_textures__);
    for (nint i = 0; i < items->length; i++) {
        StTexture_free(((StTuple2*)items->items[i])->item2);
        printf("[ASSETS] Freed texture at %s\n", ((StTuple2*)items->items[i])->item1);
    }
    StList_free_with_items(items);

    StHashMap_free(__st_textures__);
}

StTexture* StTexture_new(const char* path)
{
    // loading the same textures 385980320859 times isn't very salubrious
    if (StHashMap_contains(__st_textures__, path)) {
        return StHashMap_get(__st_textures__, path);
    }

    StTexture* dog = malloc(sizeof(StTexture));
    Texture2D mate = LoadTexture(path);
    dog->id = mate.id;
    dog->width = mate.width;
    dog->height = mate.height;
    dog->mipmaps = mate.mipmaps;
    dog->format = mate.format;
    StHashMap_set(__st_textures__, path, dog);

    printf("[ASSETS] Loaded texture at %s\n", path);
    return dog;
}

void StTexture_free(StTexture* t)
{
    // OH MY GAMMIT IT'S... tally hall
    Texture2D mmmm_mmmm_mmmm = {
        .id = t->id,
        .width = t->width,
        .height = t->height,
        .format = t->format,
        .mipmaps = t->mipmaps,
    };
    UnloadTexture(mmmm_mmmm_mmmm);
}