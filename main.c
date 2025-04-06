#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <libtrippin.h>
#include "core/core.h"
#include "player/control/player_controller.h"

// custom allocators :)
// graphics.h includes raylib
// TODO: could be better
static TrArena raylib_arena;
// static makes it complain it's not used even though it is, just in a macro
void* __rl_arena_realloc(void* ptr, size_t size)
{
	if (ptr == NULL) {
		return tr_arena_alloc(raylib_arena, size);
	}

	if (size == 0) {
		return NULL;
	}

	void* new_ptr = tr_arena_alloc(raylib_arena, size);
	if (!new_ptr) return NULL;

	memcpy(new_ptr, ptr, size);
	return new_ptr;
}
#define RL_MALLOC(sz)       tr_arena_alloc(raylib_arena, sz)
#define RL_CALLOC(n,sz)     tr_arena_alloc(raylib_arena, n * sz)
#define RL_REALLOC(ptr,sz)  rl_arena_realloc(ptr, sz)
// you can't free part of an arena
#define RL_FREE(ptr)

#include "core/graphics.h"
#include <raylib.h>

static void raylib_log_callback(int32_t level, const char* text, va_list args)
{
	const size_t buffer_size = 256;
	TrArena tmp = tr_arena_new(buffer_size);
	TrSlice buf = tr_slice_new(tmp, buffer_size, sizeof(char));
	vsnprintf(buf.buffer, buffer_size, text, args);

	// convert raylib levels to libtrippin levels
	TrLogLevel levelma;
	switch (level) {
		case LOG_WARNING: levelma = TR_LOG_WARNING; break;
		case LOG_ERROR:
		case LOG_FATAL:
			levelma = TR_LOG_ERROR;
			break;
		
		// raylib shows a comical amount of logs
		// its useful to filter that out and just make it gray
		default: levelma = TR_LOG_LIB_INFO; break;
	}

	tr_log(levelma, buf.buffer);
	tr_arena_free(tmp);
}

static void game_init(void)
{
	player_controller_new();
}

static void game_update(double dt)
{
	player_controller_update(dt);
}

static void game_free(void)
{
	player_controller_free();
}

int main(void) {
	tr_init("log.txt");
	tr_log(TR_LOG_INFO, "Stellarthing %s", ST_VERSION);
	raylib_arena = tr_arena_new(TR_MB(1));

	SetTraceLogCallback(&raylib_log_callback);
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIGHDPI);
	SetExitKey(KEY_NULL);
	InitWindow(800, 450, "stellarthing");

	graphics_init();

	game_init();

	while (!WindowShouldClose()) {
		BeginDrawing();
			ClearBackground(BLACK);
			graphics_begin_2d();
				game_update(GetFrameTime());
			graphics_end_2d();
			graphics_draw_all_3d_objects();
		EndDrawing();
	}

	graphics_free();

	game_free();

	CloseWindow();
	tr_arena_free(raylib_arena);
	tr_free();
	return 0;
}
