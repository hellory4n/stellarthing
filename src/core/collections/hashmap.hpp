#ifndef ST_HASHMAP_H
#define ST_HASHMAP_H
#include "core/core.hpp"

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
    HashMap(hash_func hash_function, hash_func length_function);
    HashMap();
    ~HashMap();

    /// returns null if it doesn't exist
    V get(K key);
    /// returns true if it's a new item
    bool set(K key, V val);
    /// if true the hashmap contains the key
    bool contains(K key);
    /// removes the key, returns true if it succeeded
    bool remove(K key);

    /// 64-bit FNV-1a hash which works for strings
    static uint64 default_hash(V* val_ptr);
    /// just a wrapper around strlen
    static uint64 default_len(V* val_ptr);

private:
    Entry* find(K key, uint64 hash);
    void resize(nint new_cap);
};

}

#endif // ST_HASHMAP_H
