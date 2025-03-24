#include <stdio.h>
#include <time.h>
#include <raylib.h>
#include "core/math/vec.h"
#include "window.h"

bool fullscreen = false;
bool closing = false;
bool ready = false;

void st_window_new(const char* title, StVec2i size)
{
	st_log("Stellarthing %s: running Starry %s", ST_GAME_VERSION, ST_STARRY_VERSION);
	
	// man
	srand(time(NULL));

	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
	// make raylib spam our log file :)
	SetTraceLogCallback(&st_rl_log_callback);
	InitWindow(size.x, size.y, title);
	SetExitKey(KEY_NULL);

	st_log("[WINDOW] Window has been created");

	ready = true;
}

void st_window_toggle_fullscreen(void)
{
	ToggleBorderlessWindowed();
	st_log("[WINDOW] Toggled fullscreen\n");
}

bool st_window_closing(void)
{
	return closing || WindowShouldClose();
}

void st_window_request_close(void)
{
	closing = true;
	st_log("[WINDOW] Window requested to be closed");
}

void st_window_free()
{
	ready = false;
	CloseWindow();
	st_log("[WINDOW] Window closed");
}

bool st_window_is_ready()
{
	return ready;
}

f64 st_window_get_time()
{
	return GetTime();
}

f64 st_window_get_delta_time()
{
	return GetFrameTime();
}

i64 st_window_get_fps()
{
	return GetFPS();
}

StVec2i st_window_get_size()
{
	i32 width = GetRenderWidth();
	i32 height = GetRenderHeight();
	return (StVec2i){width, height};
}
