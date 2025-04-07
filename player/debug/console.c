#include <raylib.h>
#include <libtrippin.h>
#include "console.h"
#include "core/graphics.h"
#include "player/control/player_controller.h"

static bool enabled;
static TrSlice input;
static size_t input_len;
static Font fontdeez;

void console_init(TrArena arena)
{
	input = tr_slice_new(arena, 256, sizeof(char));
	fontdeez = LoadFontEx("assets/ui/RedHatText-Medium.ttf", 32, NULL, 256);

	tr_log(TR_LOG_INFO, "initialized console");
}

void console_free(void)
{
	UnloadFont(fontdeez);

	tr_log(TR_LOG_INFO, "deinitialized console");
}

void console_update(void)
{
	if (IsKeyPressed(KEY_F2)) {
		enabled = !enabled;
	}

	if (!enabled) return;
	player_controller_ignore_input();

	// :(
	int32_t key = GetCharPressed();
	while (key > 0) {
		// TODO there's languages outside of western europe! did you know that? crazy i know
		// length - 1 bcuz we need 1 character for the null terminator
		if ((key >= 32) && (key <= 255) && (input_len < input.length - 1)) {
			*(char*)tr_slice_at(input, input_len) = (char)key;
			input_len++;
		}

		key = GetCharPressed();
	}

	// we all mank mistakes
	if (IsKeyPressed(KEY_BACKSPACE)) {
		input_len--;
		if (input_len < 0) input_len = 0;
		// god
		*(char*)tr_slice_at(input, input_len) = '\0';
	}

	// render
	TrColor sigma = tr_hex_rgba(0x080808ff);
	DrawRectangle(0, 0, ST_2D_RENDER_WIDTH, 40, *(Color*)(&sigma));
	DrawRectangleLines(0, 0, ST_2D_RENDER_WIDTH, 40, WHITE);
	DrawTextEx(fontdeez, input.buffer, (Vector2){8, 8}, 26, 1, WHITE);
}
