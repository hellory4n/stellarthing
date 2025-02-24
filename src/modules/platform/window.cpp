#include <stdio.h>
#include <time.h>
#include "raylib.hpp"
#include "window.hpp"

namespace starry {

bool __fullscreen = false;
bool __closing = false;
bool __ready = false;

void window::open(const char* title, Vec2i size)
{
    printf("Stellarthing %s: running Starry %s\n", ST_GAME_VERSION, ST_STARRY_VERSION);
    
    // man
    srand(time(NULL));

    rl::SetConfigFlags(rl::FLAG_VSYNC_HINT | rl::FLAG_WINDOW_RESIZABLE);
    rl::InitWindow(size.x, size.y, title);
    rl::SetExitKey(rl::KEY_NULL);
    printf("[WINDOW] Window has been created\n");

    __ready = true;
}

void window::toggle_fullscreen()
{
    rl::ToggleBorderlessWindowed();
    printf("[WINDOW] Toggled fullscreen\n");
}

bool window::closing()
{
    return __closing || rl::WindowShouldClose();
}

void window::request_close()
{
    __closing = true;
    printf("[WINDOW] Window requested to be closed\n");
}

void window::update()
{
    // put shit here
}

void window::set_target_fps(uint32 fps)
{
    rl::SetTargetFPS(fps);
}

void window::close()
{
    __ready = false;

    rl::CloseWindow();
    printf("[WINDOW] Window closed\n");
}

bool window::is_ready()
{
    return __ready;
}

float64 window::get_time()
{
    return rl::GetTime();
}

float64 window::get_delta_time()
{
    return rl::GetFrameTime();
}

int64 window::get_fps()
{
    return rl::GetFPS();
}

}
