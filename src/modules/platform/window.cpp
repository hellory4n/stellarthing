#include <stdio.h>
#include <time.h>
#include <raylib.h>
#include "window.hpp"

namespace starry {

bool __fullscreen = false;
bool __closing = false;
bool __ready = false;

void window::open(String title, Vec2i size)
{
    printf("Stellarthing %s: running Starry %s\n", ST_GAME_VERSION, ST_STARRY_VERSION);
    
    // man
    srand(time(NULL));

    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(size.x, size.y, title);
    SetExitKey(KEY_NULL);
    printf("[WINDOW] Window has been created\n");

    __ready = true;
}

void window::toggle_fullscreen()
{
    ToggleBorderlessWindowed();
    printf("[WINDOW] Toggled fullscreen\n");
}

bool window::closing()
{
    return __closing || WindowShouldClose();
}

void window::request_close()
{
    __closing = true;
    printf("[WINDOW] Window requested to be closed\n");
}

void window::update()
{
    // TODO put shit here
}

void window::set_target_fps(uint32 fps)
{
    SetTargetFPS(fps);
}

void window::close()
{
    __ready = false;

    CloseWindow();
    printf("[WINDOW] Window closed\n");
}

bool window::is_ready()
{
    return __ready;
}

float64 window::get_time()
{
    return GetTime();
}

float64 window::get_delta_time()
{
    return GetFrameTime();
}

int64 window::get_fps()
{
    return GetFPS();
}

}
