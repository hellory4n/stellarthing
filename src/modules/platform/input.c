#include <stdio.h>
#include <string.h>
#include "raylib.h"
#include "core/collections/sthashmap.h"
#include "input.h"

/// key is a string, value is a stlist of stkeys
StHashMap* __st_keymaps__;

void __st_init_input__()
{
    __st_keymaps__ = StHashMap_new(0);
}

void __st_free_input__()
{
    // sometimes you start losing your fucking mind
    StList* items = StHashMap_items(__st_keymaps__);
    for (nint i = 0; i < items->length; i++) {
        StTuple2* kvp = (StTuple2*)items->items[i];
        // we don't free the items because they're numbers
        StList_free(kvp->item2);
    }
    StList_free_with_items(items);

    StHashMap_free(__st_keymaps__);
}

bool StInput_is_key_just_pressed(StKey key)
{
    return IsKeyPressed(key);
}

bool StInput_is_key_just_released(StKey key)
{
    return IsKeyReleased(key);
}

bool StInput_is_key_held(StKey key)
{
    return IsKeyDown(key);
}

bool StInput_is_key_not_pressed(StKey key)
{
    return IsKeyUp(key);
}

bool StInput_is_mouse_button_just_pressed(StMouseButton btn)
{
    return IsMouseButtonPressed(btn);
}

bool StInput_is_mouse_button_just_released(StMouseButton btn)
{
    return IsMouseButtonReleased(btn);
}

bool StInput_is_mouse_button_held(StMouseButton btn)
{
    return IsMouseButtonDown(btn);
}

bool StInput_is_mouse_button_not_pressed(StMouseButton btn)
{
    return IsMouseButtonUp(btn);
}

void StInput_add_keymap(const char* keymap, StKey key)
{
    StList* leliste;
    if (!StHashMap_contains(__st_keymaps__, keymap)) {
        leliste = StList_new(1);
        StHashMap_set(__st_keymaps__, keymap, leliste);
    }
    else {
        leliste = StHashMap_get(__st_keymaps__, keymap);
    }

    StList_add(leliste, (void*)key);
}

bool StInput_is_keymap_just_pressed(const char* keymap)
{
    if (!StHashMap_contains(__st_keymaps__, keymap)) return false;

    StList* keys = StHashMap_get(__st_keymaps__, keymap);
    for (nint i = 0; i < keys->length; i++) {
        if (StInput_is_key_just_pressed((StKey)keys->items[i])) return true;
    }
    return false;
}

bool StInput_is_keymap_just_released(const char* keymap)
{
    if (!StHashMap_contains(__st_keymaps__, keymap)) return false;

    StList* keys = StHashMap_get(__st_keymaps__, keymap);
    for (nint i = 0; i < keys->length; i++) {
        if (StInput_is_key_just_released((StKey)keys->items[i])) return true;
    }
    return false;
}

bool StInput_is_keymap_held(const char* keymap)
{
    if (!StHashMap_contains(__st_keymaps__, keymap)) return false;

    StList* keys = StHashMap_get(__st_keymaps__, keymap);
    for (nint i = 0; i < keys->length; i++) {
        if (StInput_is_key_held((StKey)keys->items[i])) return true;
    }
    return false;
}

bool StInput_is_keymap_not_pressed(const char* keymap)
{
    if (!StHashMap_contains(__st_keymaps__, keymap)) return false;

    StList* keys = StHashMap_get(__st_keymaps__, keymap);
    for (nint i = 0; i < keys->length; i++) {
        if (StInput_is_key_not_pressed((StKey)keys->items[i])) return true;
    }
    return false;
}