#pragma once
#include "lib/hashmap.h"
#include "core/core.h"

/// this is just a wrapper around [a library i stole](https://github.com/sheredom/hashmap.h)
typedef struct hashmap_s StHashMap;

/// makes a new hash map. returns null if it failed
StHashMap* StHashMap_new(nint capacity);

/// sets an item in the hash map
void StHashMap_set(StHashMap* h, const char* key, void* val);

/// gets an item in a hash map, or null if it wasn't found
void* StHashMap_get(StHashMap* h, const char* key);

/// removes an item from the hash map, returns true if it succeeded
bool StHashMap_remove(StHashMap* h, const char* key);

/// returns the amount of items in the hash map
nint StHashMap_length(StHashMap* h);

/// frees the hash map
void StHashMap_free(StHashMap* h);