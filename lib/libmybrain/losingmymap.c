#include "losingmymap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

u64 default_hash(void *val_ptr) {
	u64 h = 14695981039346656037ULL;
	char *val = (char *) val_ptr;

	for (size_t i = 0; i < strlen(val); i++) {
		h ^= val[i];
		h *= 1099511628211ULL;
	}

	return h;
}

u64 default_len(void *val_ptr) {
	return strlen((char *) val_ptr);
}

hashmap_t new_hashmap(
		hash_func hash_function,
		hash_func length_function,
		hash_func elem_length_function,
		size_t key_size) {
	if (hash_function == NULL) hash_function = default_hash;
	if (length_function == NULL) length_function = default_len;

	if (elem_length_function == NULL) {
		fprintf(stderr, "you must provide an element length function "
				"for the new hashmap!\n");
		return (hashmap_t) {0};
	}

	hashmap_t map = {
		.entries = malloc(GOINGINSANE_INITIAL_CAPACITY * sizeof(entry_t)),
		.capacity = GOINGINSANE_INITIAL_CAPACITY,
		.count = 0,
		.hash = hash_function,
		.len = length_function,
		.elem_len = elem_length_function,
		.elem_size = key_size
	};

	if (map.entries != NULL) {
		for (int i = 0; i < GOINGINSANE_INITIAL_CAPACITY; i++) {
			entry_t *entry = &map.entries[i];

			entry->value = NULL;
			entry->key = NULL;
			entry->hash = 0;
		}
	}

	// if the entries are null it should return anyway and use that null
	// as an "error value"

	return map;
}

static entry_t *hashmap_find(
		entry_t *entries,
		size_t capacity,
		u64 hash,
		hash_func len_f,
		void *key,
		size_t elem_size) {
	u64 index = hash & (capacity - 1);

	entry_t *tombstone = NULL;

	for (;;) {
		entry_t *entry = &entries[index];

		if (entry->key == NULL) {
			if (entry->value == NULL) {
				return tombstone != NULL ? tombstone : entry;
			}

			if (tombstone == NULL) tombstone = entry;
		}

		if (hash == entry->hash) {
			size_t byte_count = len_f(entry->key) * elem_size;

			if (memcmp(entry->key, key, byte_count) == 0) {
				return entry;
			}
		}

		index = (index + 1) & (capacity - 1);
	}
}

static void resize_hashmap(hashmap_t *map, size_t new_cap) {
	entry_t *entries = malloc(sizeof(entry_t) * new_cap);

	if (entries == NULL) {
		fprintf(stderr, "hash map resize failed.\n");
		return;
	}

	for (size_t i = 0; i < new_cap; i++) {
		entries[i].key = NULL;
		entries[i].value = NULL;
		entries[i].hash = 0;
	}

	map->count = 0;
	for (size_t i = 0; i < map->capacity; i++) {
		entry_t *e = &map->entries[i];
		if (e->key == NULL) continue;

		entry_t *dest = hashmap_find(
				entries,
				new_cap,
				e->hash,
				map->len,
				e->key,
				map->elem_size);
		dest->key = e->key;
		dest->value = e->value;
		dest->hash = e->hash;
		map->count++;
	}

	free(map->entries);
	map->entries = entries;
	map->capacity = new_cap;
}

bool hashmap_set(hashmap_t *map, void *key, void *value) {
	if (map->count >= map->capacity * GOINGINSANE_MAX_LOAD) {
		resize_hashmap(map, map->capacity << 1);
	}

	u64 hash = map->hash(key);
	entry_t *entry = hashmap_find(map->entries, map->capacity, hash,
				      map->len, key, map->elem_size);

	bool new = entry->key == NULL;

	if (new && entry->value == NULL) map->count++;

	size_t num_bytes = map->elem_len(value);
	entry->value = malloc(num_bytes + num_bytes);
	memcpy(entry->value, value, num_bytes);
	memset(entry->value + num_bytes, 0, num_bytes);

	entry->hash = hash;

	num_bytes = map->elem_size * map->len(key);
	entry->key = malloc(num_bytes + map->elem_size);
	memcpy(entry->key, key, num_bytes);
	memset(entry->key + num_bytes, 0, map->elem_size);

	return new;
}

bool hashmap_get(hashmap_t *map, void *key, void *value) {
	if (map->count == 0) return false;

	u64 hash = map->hash(key);
	entry_t *entry = hashmap_find(
			map->entries,
			map->capacity,
			hash,
			map->len,
			key,
			map->elem_size);

	if (entry->key == NULL) return false;

	memcpy(value, entry->value, map->elem_len(entry->value));
	return true;
}

bool hashmap_delete(hashmap_t *map, void *key) {
	if (map->count == 0) return false;

	u64 h = map->hash(key);
	entry_t *entry = hashmap_find(
			map->entries,
			map->capacity,
			h,
			map->len,
			key,
			map->elem_size);

	if (entry->key == NULL) return false;

	free(entry->key);
	free(entry->value);

	entry->key = NULL;
	entry->value = (void *) 1;
	entry->hash = 0;
	return true;
}

void free_hashmap(hashmap_t *map) {
	for (size_t i = 0; i < map->capacity; i++) {
		entry_t *entry = &map->entries[i];
		if (entry->key == NULL) continue;
		free(entry->key);
		free(entry->value);
	}

	free(map->entries);

	*map = (hashmap_t) {0};
}
