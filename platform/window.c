#include <stdio.h>
#include <time.h>
#include <raylib.h>
#include "window.h"

bool __st_fullscreen__ = false;
bool __st_closing__ = false;
bool __st_ready__ = false;

void st_window_new(const char* title, StVec2i size)
{
	printf("Stellarthing %s: running Starry %s", ST_GAME_VERSION, ST_STARRY_VERSION);
	
	// man
	srand(time(NULL));

	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
	InitWindow(size.x, size.y, title);
	SetExitKey(KEY_NULL);
	printf("[WINDOW] Window has been created\n");

	__st_ready__ = true;
}

void st_window_toggle_fullscreen(void)
{
	ToggleBorderlessWindowed();
	printf("[WINDOW] Toggled fullscreen\n");
}

bool st_window_closing(void)
{
	return __st_closing__ || WindowShouldClose();
}

void st_window_request_close(void)
{
	__st_closing__ = true;
	printf("[WINDOW] Window requested to be closed\n");
}

void st_window_free()
{
	__st_ready__ = false;
	CloseWindow();
	printf("[WINDOW] Window closed\n");
}

bool st_window_is_ready()
{
	return __st_ready__;
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