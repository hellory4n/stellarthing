#include <stdio.h>
#include "raylib.h"
#include "core/core.h"
#include "modules/platform/window.h"
#include "modules/platform/input.h"
#include "debug_mode.h"

bool __st_enabled__ = false;

void StDebugMode_new()
{
    printf("[DEBUG MODE] Debug mode has been initialized\n");
}

void StDebugMode_update()
{
    if (StInput_is_key_just_pressed(ST_KEY_F3)) __st_enabled__ = !__st_enabled__;
    if (!__st_enabled__) return;

    char txt[256];
    // man
    sprintf(txt, "Stellarthing %s - Starry %s\n%lu FPS",
        ST_GAME_VERSION, ST_STARRY_VERSION, StWindow_get_fps());

    // shadow for contrast
    DrawText(txt,  1,  1, 16, BLACK);
    DrawText(txt,  0,  0, 16, WHITE);
}

void StDebugMode_free()
{
    printf("[DEBUG MODE] Debug mode has been freed\n");
}