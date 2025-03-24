#include "core/hashmap.h"
#include "core/math/vec.h"
#include "raylib.h"
#include "input.h"

/// key is a string, value is a stlist of stkeys
StHashMap* keymaps;

void st_init_input()
{
	keymaps = StHashMap_new(0);
}

void st_free_input()
{
	// sometimes you start losing your fucking mind
	StListKeyValue* items = StHashMap_items(keymaps);
	for (nint i = 0; i < items->length; i++) {
		StKeyValue* kvp = (StKeyValue*)items->data[i];
		// we don't free the data because they're numbers
		StList_free(kvp->val);
	}
	StList_free_all(items);

	StHashMap_free(keymaps);
}

bool st_is_key_just_pressed(StKey key)
{
	return IsKeyPressed(key);
}

bool st_is_key_just_released(StKey key)
{
	return IsKeyReleased(key);
}

bool st_is_key_held(StKey key)
{
	return IsKeyDown(key);
}

bool st_is_key_not_pressed(StKey key)
{
	return IsKeyUp(key);
}

bool st_is_mouse_button_just_pressed(StMouseButton btn)
{
	return IsMouseButtonPressed(btn);
}

bool st_is_mouse_button_just_released(StMouseButton btn)
{
	return IsMouseButtonReleased(btn);
}

bool st_is_mouse_button_held(StMouseButton btn)
{
	return IsMouseButtonDown(btn);
}

bool st_is_mouse_button_not_pressed(StMouseButton btn)
{
	return IsMouseButtonUp(btn);
}

void st_add_keymap(const char* keymap, StKey key)
{
	StList* leliste;
	if (!StHashMap_contains(keymaps, keymap)) {
		leliste = StList_new(1);
		StHashMap_set(keymaps, keymap, leliste);
	}
	else {
		leliste = StHashMap_get(keymaps, keymap);
	}

	StList_add(leliste, (void*)key);
}

bool st_is_keymap_just_pressed(const char* keymap)
{
	if (!StHashMap_contains(keymaps, keymap)) return false;

	StList* keys = StHashMap_get(keymaps, keymap);
	for (nint i = 0; i < keys->length; i++) {
		if (st_is_key_just_pressed((StKey)keys->data[i])) return true;
	}
	return false;
}

bool st_is_keymap_just_released(const char* keymap)
{
	if (!StHashMap_contains(keymaps, keymap)) return false;

	StList* keys = StHashMap_get(keymaps, keymap);
	for (nint i = 0; i < keys->length; i++) {
		if (st_is_key_just_released((StKey)keys->data[i])) return true;
	}
	return false;
}

bool st_is_keymap_held(const char* keymap)
{
	if (!StHashMap_contains(keymaps, keymap)) return false;

	StList* keys = StHashMap_get(keymaps, keymap);
	for (nint i = 0; i < keys->length; i++) {
		if (st_is_key_held((StKey)keys->data[i])) return true;
	}
	return false;
}

bool st_is_keymap_not_pressed(const char* keymap)
{
	if (!StHashMap_contains(keymaps, keymap)) return false;

	StList* keys = StHashMap_get(keymaps, keymap);
	for (nint i = 0; i < keys->length; i++) {
		if (st_is_key_not_pressed((StKey)keys->data[i])) return true;
	}
	return false;
}

StVec2 st_mouse_position()
{
	Vector2 pos = GetMousePosition();
	return (StVec2){pos.x, pos.y};
}