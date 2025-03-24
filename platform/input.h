#pragma once
#include <stdbool.h>
#include "core/math/vec.h"
#include "input_enums.h"

bool st_is_key_just_pressed(StKey key);

bool st_is_key_just_released(StKey key);

bool st_is_key_held(StKey key);

bool st_is_key_not_pressed(StKey key);

bool st_is_mouse_button_just_pressed(StMouseButton btn);

bool st_is_mouse_button_just_released(StMouseButton btn);

bool st_is_mouse_button_held(StMouseButton btn);

bool st_is_mouse_button_not_pressed(StMouseButton btn);

/// Adds a keymap. Useful to mapping keys and stuff
void st_add_keymap(const char* keymap, StKey key);

bool st_is_keymap_just_pressed(const char* keymap);

bool st_is_keymap_just_released(const char* keymap);

bool st_is_keymap_held(const char* keymap);

bool st_is_keymap_not_pressed(const char* keymap);

void st_init_input();

void st_free_input();

StVec2 st_mouse_position();
