#ifndef ST_HASHMAP_H
#define ST_HASHMAP_H
#include <string.h>
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"
#include "core/core.hpp"
#include "core/collections/list.hpp"
#include "core/collections/tuple.hpp"

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

    /// returns a list of items. remember to delete when you're done
    List<Tuple2<K*, V*>>* items()
    {
        nint size = this->size();
        auto* lmao = new List<Tuple2<K*, V*>>(size);
        for (nint i = 0; i < size; i++) {
            lmao->add(Tuple2<K*, V*>(&(this->map[i].key), &(this->map[i].value)));
        }
        return lmao;
    }

    /// if true, the key exists
    bool contains(K key)
    {
        return this->get(key) == nullptr;
    }

    ~HashMap() 
    {
        clear();
    }
};

}

#endif // ST_HASHMAP_H
