#pragma once
#include "lib/hashmap.h"
#include "core/core.h"
#include "core/collections/stlist.h"

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

/// if true, the hashmap contains that key
bool StHashMap_contains(StHashMap* h, const char* key);

/// if there's already that key, returns it. otherwise it adds the default value and returns that
void* StHashMap_get_or_add(StHashMap* h, const char* key, void* default_val);

/// converts the hashmap to a list. useful for iterating over the dictionary. remember to free it after you're done
StList* StHashMap_items(StHashMap* h);