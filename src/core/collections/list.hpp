#ifndef ST_LIST_H
#define ST_LIST_H
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

    List(nint capacity);
    ~List();
    /// adds an element to the list. returns true if it succeeded
    bool add(T item);
    /// resizes a list to a new capacity. returns true if it succeeded
    bool resize(nint new_capacity);

    T* operator [](nint idx);
};

}

#endif // ST_LIST_H
