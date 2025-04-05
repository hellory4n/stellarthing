#include <stdarg.h>
#include <stdio.h>
#include "core/core.h"
#include "libtrippin.h"
#include "player/control/player_controller.h"
#include "raylib.h"

static void raylib_log_callback(int32_t level, const char* text, va_list args)
{
	const size_t buffer_size = 256;
	TrArena tmp = tr_arena_new(buffer_size * 2);
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
	BeginDrawing();
	ClearBackground(BLACK);
	player_controller_update();
	EndDrawing();
}

static void game_free(void)
{
	player_controller_free();
}

int main(void) {
	tr_init("log.txt");
	tr_log(TR_LOG_INFO, "Stellarthing %s", ST_VERSION);
	SetTraceLogCallback(&raylib_log_callback);
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIGHDPI);
	InitWindow(800, 450, "stellarthing");

	game_init();

	while (!WindowShouldClose()) {
		game_update(GetFrameTime());
	}

	game_free();

	CloseWindow();
	tr_free();
	return 0;
}
