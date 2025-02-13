#include <stdio.h>
#include <raylib.h>
#include "modules/graphics/texture.h"
#include "modules/audio/audio.h"
#include "modules/util/timer.h"
#include "modules/util/tween.h"
#include "input.h"
#include "window.h"

bool __st_fullscreen__ = false;
bool __st_closing__ = false;
bool __st_ready__ = false;

void StWindow_new(const char* title, stvec2i size)
{
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(size.x, size.y, title);
    SetExitKey(KEY_NULL);
    printf("[WINDOW] Window has been created\n");

    // start subsystems
    __st_init_textures__();
    __st_init_input__();
    __st_init_audio__();
    __st_init_timers__();
    __st_init_tweens__();

    __st_ready__ = true;
}

void StWindow_toggle_fullscreen()
{
    ToggleBorderlessWindowed();
    printf("[WINDOW] Toggled fullscreen\n");
}

bool StWindow_closing()
{
    return __st_closing__ || WindowShouldClose();
}

void StWindow_close()
{
    __st_closing__ = true;
    printf("[WINDOW] Window requested to be closed\n");
}

void StWindow_update()
{
    // update subsystems
    __st_update_timers__();
    __st_update_tweens__();
}

void StWindow_set_target_fps(uint32 fps)
{
    SetTargetFPS(fps);
}

void StWindow_free()
{
    __st_ready__ = false;

    // clean up subsystems
    __st_free_textures__();
    __st_free_input__();
    __st_free_audio__();
    __st_free_timers__();
    __st_free_tweens__();

    CloseWindow();
    printf("[WINDOW] Window closed\n");
}

bool StWindow_is_ready()
{
    return __st_ready__;
}

float64 StWindow_get_time()
{
    return GetTime();
}

float64 StWindow_get_delta_time()
{
    return GetFrameTime();
}

int64 StWindow_get_fps()
{
    return GetFPS();
}