#pragma once
#include "input_enums.h"

bool StInput_is_key_just_pressed(StKey key);

bool StInput_is_key_just_released(StKey key);

bool StInput_is_key_held(StKey key);

bool StInput_is_key_not_pressed(StKey key);

bool StInput_is_mouse_button_just_pressed(StMouseButton btn);

bool StInput_is_mouse_button_just_released(StMouseButton btn);

bool StInput_is_mouse_button_held(StMouseButton btn);

bool StInput_is_mouse_button_not_pressed(StMouseButton btn);

/// adds a keymap. useful to mapping keys and stuff
void StInput_add_keymap(const char* keymap, StKey key);

bool StInput_is_keymap_just_pressed(const char* keymap);

bool StInput_is_keymap_just_released(const char* keymap);

bool StInput_is_keymap_held(const char* keymap);

bool StInput_is_keymap_not_pressed(const char* keymap);

void __st_init_input__();

void __st_free_input__();