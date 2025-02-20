#include <stdio.h>
#include <string.h>
#include "list.hpp"

namespace starry {

template<typename T>
List<T>::List(nint capacity)
{
    this->items = malloc(capacity * sizeof(T));
    this->capacity = capacity;
    this->length = 0;
}

template<typename T>
List<T>::~List()
{
    free(this->items);
}

template<typename T>
bool List<T>::resize(nint new_capacity)
{
    T* new_data = realloc(this->items, new_capacity * sizeof(T));
    if (new_data == NULL) {
        fprintf(stderr, "[CORE] Memory reallocation error\n");
        return false;
    }

    this->items = new_data;
    this->capacity = new_capacity;
    return true;
}

template<typename T>
bool List<T>::add(T item)
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

template<typename T>
T* List<T>::operator [](nint idx)
{
    // not a huge fan of segfaults
    if (idx >= this->length) {
        fprintf(stderr, "[CORE] Index out of range\n");
        // a segfault is about to happen!
        fflush(stdout);
        return NULL;
    }
    
    return &(((T*)this->items)[idx]);
}

}