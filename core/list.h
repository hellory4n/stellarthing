#pragma once
#include "core/core.h"

/// Similar to a Go slice. Not only it's a an array with a size, but it also allows adding items, which
/// is quite handsome. It's recommended to make typedefs around StList, e.g. `StListThingamabob`, for
/// clarity.
typedef struct {
	/// Internal array of items
	void** data;
	/// How many items the internal array can hold
	nint capacity;
	/// How many items the array already has
	nint length;
} StList;

/// Creates a new list, or null if it fails
StList* StList_new(nint capacity);

/// Adds an element to the list. Returns true if it succeeded
bool StList_add(StList* l, void* item);

/// Resizes a list to a new capacity. Returns true if it succeeded
bool StList_resize(StList* l, nint new_capacity);

/// Gets the item at the index, or null if it wasn't found. You could just index the data variable,
/// but this function actually says something if a segfault happens
void* StList_at(StList* l, nint idx);

/// Sets the item at the index, returns true if it succeded
bool StList_set(StList* l, nint idx, void* item);

/// Frees the list. If the items are heap allocated you should manually free them before calling
/// this. if you want to just call `free()` to every item, use `StList_free_all()`
void StList_free(StList* l);

/// Similar to `StList_free()`, but it also calls `free()` to every item. If your items are more
/// complicated than that then you can manually free the items and then call `StList_free()`
void StList_free_all(StList* l);