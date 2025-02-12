#include <stdio.h>
#include <raylib.h>
#include "modules/graphics/texture.h"
#include "modules/audio/audio.h"
#include "input.h"
#include "window.h"

bool __st_fullscreen__ = false;
bool __st_closing__ = false;
bool __st_ready__ = false;

void StWindow_create(const char* title, stvec2i size)
{
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(size.x, size.y, title);
    SetExitKey(KEY_NULL);
    printf("[WINDOW] Window has been created\n");

    // start subsystems
    __st_init_textures__();
    __st_init_input__();
    __st_init_audio__();

    __st_ready__ = true;
}

void StWindow_set_fullscreen(bool fullscreen)
{
    if (fullscreen) SetConfigFlags(FLAG_BORDERLESS_WINDOWED_MODE);
    else SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    __st_fullscreen__ = fullscreen;
    
    printf("[WINDOW] Window is now fullscreen\n");
}

bool StWindow_fullscreen()
{
    return __st_fullscreen__;
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