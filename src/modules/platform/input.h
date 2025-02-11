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