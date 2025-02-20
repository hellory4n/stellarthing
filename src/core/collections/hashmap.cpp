#include <string.h>
#include <stdio.h>
#include "hashmap.hpp"

namespace starry {

template<typename K, typename V>
HashMap<K, V>::HashMap(hash_func hash_function, hash_func len_function)
{
    if (hash_function == nullptr) hash_function = default_hash;
    if (len_function == nullptr) len_function = default_len;

    this->entries = malloc(ST_HASHMAP_INITIAL_CAPACITY * sizeof(V));
    this->count = 0;
    this->hash = hash_function;
    this->len = len_function;
    this->key_type_size = sizeof(K);

    if (this->entries != nullptr) {
		for (int i = 0; i < ST_HASHMAP_INITIAL_CAPACITY; i++) {
			Entry* entry = &this->entries[i];
			entry->val = nullptr;
			entry->key = nullptr;
			entry->hash = 0;
		}
	}
}

template<typename K, typename V>
HashMap<K, V>::HashMap()
{
    HashMap(nullptr, nullptr);
}

template<typename K, typename V>
typename HashMap<K, V>::Entry* HashMap<K, V>::find(K key, uint64 hash)
{
    uint64 index = hash & (this->capacity - 1);
    Entry* tombstone = nullptr;

	for (;;) {
		Entry* entry = &this->entries[index];

		if (entry->key == nullptr) {
			if (entry->val == nullptr) {
				return tombstone != nullptr ? tombstone : entry;
			}

			if (tombstone == nullptr) tombstone = entry;
		}

		if (hash == entry->hash) {
			nint byte_count = this->lenf(entry->key) * this->key_type_size;
			if (memcmp(entry->key, key, byte_count) == 0) {
				return entry;
			}
		}

		index = (index + 1) & (this->capacity - 1);
	}
    return nullptr;
}

template<typename K, typename V>
void HashMap<K, V>::resize(nint new_cap)
{
	Entry* entries = malloc(sizeof(Entry) * new_cap);

	if (entries == nullptr) {
		fprintf(stderr, "[CORE] Hash map resize failed.\n");
		return;
	}

	for (nint i = 0; i < new_cap; i++) {
		entries[i].key = nullptr;
		entries[i].val = nullptr;
		entries[i].hash = 0;
	}

	this->count = 0;
	for (nint i = 0; i < this->capacity; i++) {
		Entry* e = &this->entries[i];
		if (e->key == nullptr) continue;

		Entry* dest = this->find(e->key, e->hash);
		dest->key = e->key;
		dest->val = e->val;
		dest->hash = e->hash;
		this->count++;
	}

	free(this->entries);
	this->entries = entries;
	this->capacity = new_cap;
}

template<typename K, typename V>
V HashMap<K, V>::get(K key)
{
    if (this->count == 0) return nullptr;

	uint64 hash = this->hashf(key);
	Entry* entry = this->find(hash, key);

	if (entry->key == nullptr) return nullptr;

    V* val;
	memcpy(val, entry->val, sizeof(entry->val));
    return *val;
}

template<typename K, typename V>
bool HashMap<K, V>::set(K key, V val)
{
    if (this->count >= this->capacity * ST_HASHMAP_MAX_LOAD) {
		this->resize(this->capacity << 1);
	}

	uint64 hash = this->hashf(key);
	Entry* entry = this->find(key, hash);

	bool neww = entry->key == nullptr;

	if (neww && entry->val == nullptr) this->count++;

	nint num_bytes = sizeof(val);
	entry->val = malloc(num_bytes + num_bytes);
	memcpy(entry->val, val, num_bytes);
	memset(entry->val + num_bytes, 0, num_bytes);

	entry->hash = hash;

	num_bytes = this->key_type_size * this->lenf(key);
	entry->key = malloc(num_bytes + this->key_type_size);
	memcpy(entry->key, key, num_bytes);
	memset(entry->key + num_bytes, 0, this->key_type_size);

	return neww;
}

template<typename K, typename V>
bool HashMap<K, V>::remove(K key)
{
    if (this->count == 0) return false;

	uint64 h = this->hashf(key);
	Entry* entry = this->find(key, h);

	if (entry->key == nullptr) return false;

	free(entry->key);
	free(entry->val);

	entry->key = nullptr;
    // i know
	entry->val = (void*)1;
	entry->hash = 0;
	return true;
}

template<typename K, typename V>
HashMap<K, V>::~HashMap()
{
    for (nint i = 0; i < this->capacity; i++) {
		Entry* entry = &this->entries[i];
		if (entry->key == nullptr) continue;
		free(entry->key);
		free(entry->val);
	}
    free(this->entries);
}

template<typename K, typename V>
uint64 HashMap<K, V>::default_hash(V* val_ptr)
{
    uint64 h = 14695981039346656037ULL;
	char* val = (char*)val_ptr;

	for (nint i = 0; i < strlen(val); i++) {
		h ^= val[i];
		h *= 1099511628211ULL;
	}

	return h;
}

template<typename K, typename V>
uint64 HashMap<K, V>::default_len(V* val_ptr)
{
    return strlen((char*)val_ptr);
}

template<typename K, typename V>
bool HashMap<K, V>::contains(K key)
{
    V* val = nullptr;
    bool exists = this->get(key, val);
    return exists;
}

}