#ifndef LOSINGMYMAP_H
#define LOSINGMYMAP_H

#include "libmybrain.h"

#define GOINGINSANE_INITIAL_CAPACITY 32
#define GOINGINSANE_MAX_LOAD 0.75

typedef struct {
	void *key;
	void *value;
	u64 hash;
} entry_t;

typedef u64 (*hash_func) (void *val_ptr);

// 64-bit FNV-1a hash which works for strings.
u64 default_hash(void *val_ptr);

// Just a wrapper around strlen
u64 default_len(void *val_ptr);

typedef struct overtime_map {
	entry_t *entries;
	size_t capacity;
	size_t count;
	size_t elem_size;
	hash_func hash;
	hash_func len;
	hash_func elem_len;
} hashmap_t;

/*
 * creates a hashmap where the key is made from elements of size key_size
 * map.entries is NULL on failure.
 */
hashmap_t new_hashmap(
		hash_func hash_function,
		hash_func length_function,
		hash_func element_length_function,
		size_t key_size);

bool hashmap_set(hashmap_t *map, void *key, void *value);
bool hashmap_get(hashmap_t *map, void *key, void *value);
bool hashmap_delete(hashmap_t *map, void *key);

void free_hashmap(hashmap_t *map);

#endif // LOSINGMYMAP_H
