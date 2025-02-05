#pragma once
#include "core/core.h"

/// dynamically sized list
typedef struct {
    void* items;
    nint capacity;
    nint length;
} StList;

/// creates a new list
StList* StList_new(nint capacity);
/// adds an element to the list. returns true if it succeeded
bool StList_add(StList* l, void* item);
/// frees the list. if the items are heap allocated you should manually free them before calling this.
void StList_free(StList* l);
/// resizes a list to a new capacity. returns true if it succeeded
bool StList_resize(StList* l, nint new_capacity);
/// gets the item at the index, or null if it wasn't found
void* StList_at(StList* l, nint idx);
/// sets the item at the index
void StList_set(StList* l, nint idx, void* item);