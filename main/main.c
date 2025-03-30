#include "core/core.h"
#include "core/math/color.h"
#include "core/math/vec.h"
#include "game/generator/world/world_gen.h"
#include "game/player/player.h"
#include "misc/debug/console.h"
#include "misc/debug/debug_mode.h"
#include "misc/ui/ui.h"
#include "platform/graphics/model.h"
#include "platform/graphics/texture.h"
#include "platform/window.h"
#include "platform/graphics/graphics.h"
#include "platform/input.h"

// StModel* mate;

static void init_game(void)
{
	st_init_player();

	// generate the bloody world
	StTerrainPart* world = st_gen_chunk(42069, 0, 0);
	// mate = st_gen_chunk_mesh(world);
	free(world);
}

static void update_game(void)
{
	st_update_player();

	// st_draw_object_3d((StObject3D){
	// 	.model = mate,
	// 	.position = (StVec3){0, 0, 0},
	// 	.rotation = 0,
	// 	.scale = (StVec3){1, 1, 1},
	// 	.tint = ST_WHITE,
	// });
}

static void free_game(void)
{
	st_free_player();

	// UnloadModel(*(Model*)mate);
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
	st_init_console();

	init_game();

	while (!st_window_closing()) {
		st_clear(ST_BLACK);

		// before the 2d stuff because 2d is used for ui stuff
		st_draw_all_3d_objects();

		st_early_update_ui();
		st_update_debug_mode();
		st_update_console();
		update_game();
		st_late_update_ui();

		st_end_drawing();
	}

	free_game();

	st_free_console();
	st_free_ui();
	st_free_lighting();
	st_free_models();
	st_free_textures();
	st_free_input();
	st_window_free();
	st_free_logging();
	return 0;
}