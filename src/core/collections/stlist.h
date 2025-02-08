#pragma once
#include "../core.h"

/// dynamically sized list
typedef struct {
    /// internal array of items
    void** items;
    /// how many items the internal array can hold
    nint capacity;
    /// how many items the array already has
    nint length;
} StList;

/// creates a new list
StList* StList_new(nint capacity);

/// adds an element to the list. returns true if it succeeded
bool StList_add(StList* l, void* item);

/// resizes a list to a new capacity. returns true if it succeeded
bool StList_resize(StList* l, nint new_capacity);

/// gets the item at the index, or null if it wasn't found
void* StList_at(StList* l, nint idx);

/// sets the item at the index
void StList_set(StList* l, nint idx, void* item);

/// frees the list. if the items are heap allocated you should manually free them before calling this. if you want to just call `free()` to every item, use `StList_free_with_items()`
void StList_free(StList* l);

/// similar to `StList_free()`, but it also calls `free()` to every item. if your items are more complicated than that then you can manually free the items and then call `StList_free()`
void StList_free_with_items(StList* l);