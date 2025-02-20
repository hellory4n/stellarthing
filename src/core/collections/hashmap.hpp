#ifndef ST_HASHMAP_H
#define ST_HASHMAP_H
#include "core/core.hpp"
#include <string.h>

namespace starry {

#define ST_HASHMAP_INITIAL_CAPACITY 32
#define ST_HASHMAP_MAX_LOAD 0.75

// STOLEN FROM KRALL LIBMYBRAINISWORKINGOVERTIME LOSING MY MAP DOT H https://codeberg.org/krall2125/libmybrainisworkingovertime
template<typename K, typename V>
class HashMap {
public:
    /// hash function
    typedef uint64 (*hash_func) (V* val_ptr);
    
    struct Entry {
        K* key;
        V* val;
        uint64 hash;
    };

    /// this is an array
    Entry* entries;
    /// how much the hashmap can hold
    nint capacity;
    /// how many items the hashmap has
    nint count;
    /// as the name implies it's the size of the type of the key
    nint key_type_size;
    hash_func hashf;
    hash_func lenf;

    /// make a hashmap with custom function stuff
    HashMap(hash_func hash_function, hash_func length_function)
    {
        if (hash_function == nullptr) hash_function = default_hash;
        if (length_function == nullptr) length_function = default_len;

        this->entries = (Entry*)malloc(ST_HASHMAP_INITIAL_CAPACITY * sizeof(V));
        this->count = 0;
        this->hashf = hash_function;
        this->lenf = length_function;
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

    HashMap()
    {
        HashMap(nullptr, nullptr);
    }

    ~HashMap()
    {
        for (nint i = 0; i < this->capacity; i++) {
            Entry* entry = &this->entries[i];
            if (entry->key == nullptr) continue;
            free((void*)entry->key);
            free((void*)entry->val);
        }
        free(this->entries);
    }

    /// 64-bit FNV-1a hash which works for strings
    static uint64 default_hash(V* val_ptr)
    {
        uint64 h = 14695981039346656037ULL;
        char* val = (char*)val_ptr;

        for (nint i = 0; i < strlen(val); i++) {
            h ^= val[i];
            h *= 1099511628211ULL;
        }

        return h;
    }

    /// just a wrapper around strlen
    static uint64 default_len(V* val_ptr)
    {
        return strlen((char*)val_ptr);
    }

    Entry* find(K* key, uint64 hash)
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

    void resize(nint new_cap)
    {
        Entry* entries = (Entry*)malloc(sizeof(Entry) * new_cap);

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

    /// returns null if it doesn't exist
    V* get(K* key)
    {
        if (this->count == 0) return nullptr;

        uint64 hash = this->hashf(key);
        Entry* entry = this->find(key, hash);

        if (entry->key == nullptr) return nullptr;

        V* val = nullptr;
        memcpy((void*)val, entry->val, sizeof(entry->val));
        return val;
    }

    /// returns true if it's a new item
    bool set(K* key, V* val)
    {
        if (this->count >= this->capacity * ST_HASHMAP_MAX_LOAD) {
            this->resize(this->capacity << 1);
        }

        uint64 hash = this->hashf(key);
        Entry* entry = this->find(key, hash);

        bool neww = entry->key == nullptr;

        if (neww && entry->val == nullptr) this->count++;

        nint num_bytes = sizeof(val);
        entry->val = (V*)malloc(num_bytes + num_bytes);
        // the cast is to remove the const part in strings lmao
        memcpy((void*)entry->val, val, num_bytes);
        memset((void*)entry->val + num_bytes, 0, num_bytes);

        entry->hash = hash;

        num_bytes = this->key_type_size * this->lenf(key);
        entry->key = (K*)malloc(num_bytes + this->key_type_size);
        memcpy((void*)entry->key, key, num_bytes);
        memset((void*)entry->key + num_bytes, 0, this->key_type_size);

        return neww;
    }

    /// if true the hashmap contains the key
    bool contains(K* key)
    {
        V* val = nullptr;
        bool exists = this->get(key, val);
        return exists;
    }

    /// removes the key, returns true if it succeeded
    bool remove(K* key)
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
};

}

#endif // ST_HASHMAP_H
