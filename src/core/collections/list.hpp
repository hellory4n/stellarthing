#ifndef ST_LIST_H
#define ST_LIST_H
#include <stdio.h>
#include "core/core.hpp"

namespace starry {

template<typename T>
class List {
public:
    /// internal array of items
    T* items;
    /// how many items the internal array can hold
    nint capacity;
    /// how many items the array already has
    nint length;

    List(nint capacity)
    {
        this->items = (T*)malloc(capacity * sizeof(T));
        this->capacity = capacity;
        this->length = 0;
    }

    ~List()
    {
        free(this->items);
    }

    /// resizes a list to a new capacity. returns true if it succeeded
    bool resize(nint new_capacity)
    {
        T* new_data = (T*)realloc(this->items, new_capacity * sizeof(T));
        if (new_data == NULL) {
            fprintf(stderr, "[CORE] Memory reallocation error\n");
            return false;
        }

        this->items = new_data;
        this->capacity = new_capacity;
        return true;
    }

    /// adds an element to the list. returns true if it succeeded
    bool add(T item)
    {
        if (this->length >= this->capacity) {
            nint new_cap = this->capacity * 2 + 1;
            if (!this->resize(new_cap)) {
                return false;
            }
        }

        this->items[this->length] = item;
        this->length++;
        return true;
    }

    /// returns the item at a certain index
    T* at(nint idx)
    {
        // not a huge fan of segfaults
        if (idx >= this->length) {
            fprintf(stderr, "[CORE] Index out of range: index is %lu, length is %lu\n", idx, this->length);
            // a segfault is about to happen!
            fflush(stderr);
            return nullptr;
        }
        
        return &(((T*)this->items)[idx]);
    }
};

}

#endif // ST_LIST_H
