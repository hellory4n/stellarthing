#include "core/core.h"
#include "core/math/color.h"
#include "core/math/math.h"
#include "core/math/vec.h"
#include "game/generator/world/world_gen.h"
#include "game/player/player.h"
#include "misc/debug/debug_mode.h"
#include "misc/ui/ui.h"
#include "platform/graphics/model.h"
#include "platform/graphics/texture.h"
#include "platform/window.h"
#include "platform/graphics/graphics.h"
#include "platform/input.h"
#include "raylib.h"

Texture bloodyworldlbodoyelophmalte;

static void init_game(void)
{
	st_init_player();

	// generate the bloody world
	i64* bloody_world = malloc(256 * 256 * sizeof(i64));
	Image please = GenImageColor(256, 256, WHITE);

	for (i64 z = 0; z < 256; z++) {
		for (i64 x = 0; x < 256; x++) {
			f64 height = st_gen_get_block_height(42069, x, z);
			// it doesn't let me do [x][z]
			bloody_world[x * 256 + z] = height;

			// color
			// the range is -1 to 1 except not really??
			Color color;
			if (height < -0.6 / 2) {
				color = DARKBLUE;
			}
			else if (height < -0.3 / 2) {
				color = BLUE;
			}
			else if (height < -0.1 / 2) {
				color = SKYBLUE;
			}
			else if (height < 0.0) {
				color = (Color){0xf0, 0xf4, 0xc3, 0xff};
			}
			else if (height < 0.2 / 2) {
				color = GREEN;
			}
			else if (height < 0.4 / 2) {
				color = LIME;
			}
			else if (height < 0.6 / 2) {
				color = DARKGREEN;
			}
			else if (height < 0.75 / 2) {
				color = (Color){96, 130, 145, 0xff};
			}
			else if (height < 0.9 / 2) {
				color = DARKGRAY;
			}
			else {
				color = WHITE;
			}
			ImageDrawPixel(&please, x, z, color);
		}
	}

	bloodyworldlbodoyelophmalte = LoadTextureFromImage(please);
	UnloadImage(please);
	free(bloody_world);
}

static void update_game(void)
{
	st_update_player();

	DrawTextureEx(bloodyworldlbodoyelophmalte, (Vector2){16, 16}, 0, 2.5, WHITE);
}

static void free_game(void)
{
	st_free_player();

	UnloadTexture(bloodyworldlbodoyelophmalte);
}

int main(int argc, const char* argv[])
{
	st_init_logging();
	st_window_new("Stellarthing", (StVec2i){1280, 720});
	//st_window_toggle_fullscreen();
	st_init_input();
	st_init_textures();
	st_init_models();
	st_init_lighting();
	st_init_ui();

	init_game();

	while (!st_window_closing()) {
		st_clear(ST_BLACK);

		// before the 2d stuff because 2d is used for ui stuff
		st_draw_all_3d_objects();

		st_early_update_ui();
		st_update_debug_mode();
		update_game();
		st_late_update_ui();

		st_end_drawing();
	}

	free_game();

	st_free_ui();
	st_free_lighting();
	st_free_models();
	st_free_textures();
	st_free_input();
	st_window_free();
	st_free_logging();
	return 0;
}
