#pragma once
#include "lib/hashmap.h"
#include "core/core.h"
#include "core/list.h"

/// It's an item in a hashmap
typedef struct {
	void* key;
	void* val;
} StKeyValue;

typedef StList StListKeyValue;

/// This is just a wrapper around [a library i stole](https://github.com/sheredom/hashmap.h)
typedef struct hashmap_s StHashMap;

/// Makes a new hash map. returns null if it failed
StHashMap* StHashMap_new(nint capacity);

/// Sets an item in the hash map
void StHashMap_set(StHashMap* h, const char* key, void* val);

/// Gets an item in a hash map, or null if it wasn't found
void* StHashMap_get(StHashMap* h, const char* key);

/// Removes an item from the hash map, returns true if it succeeded
bool StHashMap_remove(StHashMap* h, const char* key);

/// Returns the amount of items in the hash map
nint StHashMap_length(StHashMap* h);

/// Frees the hash map
void StHashMap_free(StHashMap* h);

/// If true, the hashmap contains that key
bool StHashMap_contains(StHashMap* h, const char* key);

/// If there's already that key, returns it. Otherwise it adds the default value and returns that
void* StHashMap_get_or_add(StHashMap* h, const char* key, void* default_val);

/// Converts the hashmap to a list. Useful for iterating over the dictionary. Remember to free it
/// after you're done, with `StList_free_all()`
StListKeyValue* StHashMap_items(StHashMap* h);