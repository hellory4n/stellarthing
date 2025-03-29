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
#include <stdlib.h>

Texture bloodyworldlbodoyelophmalte;

static void init_game(void)
{
	st_init_player();

	// generate the bloody world
	const i64 width = 256;
	const i64 height = 256;
	
	i64* bloody_world = malloc(256 * 256 * sizeof(i64));

	Mesh meshma;
	meshma.vertexCount = width * height;
	meshma.triangleCount = (width - 1) * (height - 1) * 6;
	meshma.vertices = malloc(meshma.vertexCount * sizeof(float) * 3);
	meshma.texcoords = malloc(meshma.vertexCount * sizeof(float) * 2);

	nint vertices = 0;

	// add triangle
	// meshma.vertices[triangle_idx] = x;
	// meshma.vertices[triangle_idx + 1] = y;
	// meshma.vertices[triangle_idx + 2] = z;
	// triangle_idx += 3;

	f32 top_left_x = (width - 1) / -2.0f;
	f32 top_left_z = (height - 1) / 2.0f;

	nint vert_idx_smth = 0;
	for (i64 z = 0; z < width; z++) {
		for (i64 x = 0; x < height; x++) {
			f64 y = st_gen_get_block_height(42069, x, z);
			// it doesn't let me do [x][z]
			bloody_world[x * width + z] = y;

			StColor bloody_colour = st_gen_get_color(y);

			// mesh deez
			meshma.vertices[vertices] = top_left_x + x;
			meshma.vertices[vertices + 1] = y;
			meshma.vertices[vertices + 2] =  top_left_z - z;
			vertices += 3;

			meshma.vertices[vertices] = top_left_x + x + 1;
			meshma.vertices[vertices + 1] = y;
			meshma.vertices[vertices + 2] =  top_left_z - z;
			vertices += 3;

			meshma.vertices[vertices] = top_left_x + x + 1;
			meshma.vertices[vertices + 1] = y;
			meshma.vertices[vertices + 2] =  top_left_z - z + 1;
			vertices += 3;

			meshma.vertices[vertices] = top_left_x + x;
			meshma.vertices[vertices + 1] = y;
			meshma.vertices[vertices + 2] =  top_left_z - z;
			vertices += 3;

			meshma.vertices[vertices] = top_left_x + x;
			meshma.vertices[vertices + 1] = y;
			meshma.vertices[vertices + 2] =  top_left_z - z + 1;
			vertices += 3;

			meshma.vertices[vertices] = top_left_x + x + 1;
			meshma.vertices[vertices + 1] = y;
			meshma.vertices[vertices + 2] =  top_left_z - z + 1;
			vertices += 3;

			if (x < width - 1 && y < height - 1) {

			}

			vert_idx_smth++;
		}
	}

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
