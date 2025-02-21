#ifndef ST_HASHMAP_H
#define ST_HASHMAP_H
namespace libmybrain {
    extern "C" {
        #include "libmybrain/losingmymap.h"
    }
}
#include "core/core.hpp"
#include <string.h>

namespace starry {

#define ST_HASHMAP_INITIAL_CAPACITY 32
#define ST_HASHMAP_MAX_LOAD 0.75

// STOLEN FROM KRALL LIBMYBRAINISWORKINGOVERTIME LOSING MY MAP DOT H https://codeberg.org/krall2125/libmybrainisworkingovertime
template<typename K, typename V>
class HashMap {
private:
    libmybrain::hashmap_t __map;

    static uint64 len_func(void* val)
    {
        return sizeof(K);
    }
public:
    HashMap()
    {
        this->__map = libmybrain::new_hashmap(libmybrain::default_hash, libmybrain::default_len, &len_func, sizeof(K));
    }

    ~HashMap()
    {
        libmybrain::free_hashmap(&this->__map);
    }

    /// returns null if it doesn't exist
    V* get(K* key)
    {
        void* lmao = nullptr;
        libmybrain::hashmap_get(&this->__map, (void*)key, &lmao);
        return (V*)lmao;
    }

    /// returns true if it's a new item
    bool set(K* key, V* val)
    {
        return libmybrain::hashmap_set(&this->__map, (void*)key, (void*)val);
    }

    /// removes the key, returns true if it succeeded
    bool remove(K* key)
    {
        return libmybrain::hashmap_delete(&this->__map, (void*)key);
    }

    /// if true the hashmap contains the key
    bool contains(K* key)
    {
        return this->get(key) != nullptr;
    }
};

}

#endif // ST_HASHMAP_H
