#include <stdio.h>
#include <string.h>
#include "hashmap.h"
#include "core/core.h"

StHashMap* StHashMap_new(nint capacity)
{
	StHashMap* mate = malloc(sizeof(StHashMap));
	if (hashmap_create(capacity, mate) != 0) {
		st_log("Let's take a hashmap and initialize it. Oh look, hashmap's busted");
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
		st_log("Key probably doesn't exist or something I didn't write this");
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

StList* StHashMap_items(StHashMap* h)
{
	StList* lsit = StList_new(h->size);
	for (nint i = 1; i < h->size + 1; i++) {
		struct hashmap_element_s m = h->data[i];

		if (!m.in_use) continue;

		StKeyValue* pair = malloc(sizeof(StKeyValue));
		pair->key = (void*)m.key;
		pair->val = m.data;

		StList_add(lsit, pair);
	}
	return lsit;
}