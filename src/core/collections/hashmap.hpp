#ifndef ST_HASHMAP_H
#define ST_HASHMAP_H
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"
#include "core/core.hpp"
#include <string.h>

namespace starry {

template <typename K, typename V>
class HashMap {
    struct { K key; V value; }* map = nullptr;
public:
    /// sets
    void set(K key, V value)
    {
        hmput(this->map, key, value);
    }

    /// gets (returns null if it doesn't exist)
    V* get(K key)
    {
        // the struct is unnamed
        auto* entry = hmgetp(map, key);
        return entry ? &entry->value : nullptr;
    }

    /// size of the hashmap
    nint size()
    {
        return hmlen(this->map);
    }

    /// clears the hashmap
    void clear()
    {
        hmfree(this->map);
        this->map = nullptr;
    }

    ~HashMap() 
    {
        clear();
    }
};

}

#endif // ST_HASHMAP_H
