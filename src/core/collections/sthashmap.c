#include <stdio.h>
#include "sthashmap.h"

StHashMap* StHashMap_new(nint capacity)
{
    StHashMap* mate = malloc(sizeof(StHashMap));
    if (hashmap_create(capacity, mate) != 0) {
        fprintf(stderr, "Let's take a hashmap and initialize it. Oh look, hashmap's busted.\n");
        return NULL;
    }
    return mate;
}

void StHashMap_set(StHashMap* h, const char* key, void* val)
{
    hashmap_put(h, key, strlen(key), val);
}

void* StHashMap_get(StHashMap* h, const char* key)
{
    return hashmap_get(h, key, strlen(key));
}

bool StHashMap_remove(StHashMap* h, const char* key)
{
    if (hashmap_remove(h, key, strlen(key)) != 0) {
        fprintf(stderr, "Key probably doesn't exist or something I didn't write this.\n");
        return false;
    }
    return true;
}

nint StHashMap_length(StHashMap* h)
{
    return hashmap_num_entries(h);
}

void StHashMap_free(StHashMap* h)
{
    hashmap_destroy(h);
}