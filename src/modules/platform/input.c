#include "raylib.h"
#include "input.h"

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