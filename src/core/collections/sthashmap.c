#include <stdio.h>
#include <string.h>
#include "core/collections/sttuple.h"
#include "sthashmap.h"
#include "core/starry.h"

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

nint StHashMap_capacity(StHashMap* h)
{
    return hashmap_capacity(h);
}

void StHashMap_free(StHashMap* h)
{
    hashmap_destroy(h);
}

bool StHashMap_contains(StHashMap* h, const char* key)
{
    return StHashMap_get(h, key) != NULL;
}

void* StHashMap_get_or_add(StHashMap* h, const char* key, void* default_val)
{
    if (StHashMap_contains(h, key)) {
        return StHashMap_get(h, key);
    }
    else {
        StHashMap_set(h, key, default_val);
        return default_val;
    }
}

static int __st_man__(void* list, struct hashmap_element_s* const e)
{
    printf("Man.1\n");
    fflush(stdout);
    if (!e->in_use) return 0;
    printf("Man.2\n");
    fflush(stdout);

    const char lekey[e->key_len];
    strncpy(lekey, e->key, e->key_len);
    printf("Man.3\n");
    fflush(stdout);

    StTuple2* pair = malloc(sizeof(StTuple2));
    printf("Man.4\n");
    fflush(stdout);
    pair->item1 = lekey;
    pair->item2 = e->data;
    printf("Man.5\n");
    fflush(stdout);
    StList_add(list, pair);
    printf("Man.6\n");
    fflush(stdout);
}

StList* StHashMap_items(StHashMap* h)
{
    StList* man = StList_new(StHashMap_capacity(h));
    hashmap_iterate_pairs(h, &__st_man__, &man);
    return man;
}