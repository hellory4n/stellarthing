#include <stdio.h>
#include "core/math/color.h"
#include "core/math/vec.h"
#include "core/stack.h"
#include "misc/debug/debug_mode.h"
#include "misc/ui/ui.h"
#include "platform/graphics/model.h"
#include "platform/graphics/texture.h"
#include "platform/window.h"
#include "platform/graphics/graphics.h"
#include "platform/input.h"

StTexture* m;
StModel* suzanne;
StVec3 rot;

static void init_game(void)
{
	st_set_camera((StCamera){
		.position = (StVec3){0.5, 5, 5},
		.target = (StVec3){0, 0, 0},
		.fov = 90,
		.perspective = true,
	});

	// mate
	st_add_keymap("test_move", ST_KEY_SPACE);
	st_add_keymap("test_move", ST_KEY_NUM6);
	st_add_keymap("test_move", ST_KEY_J);

	m = StTexture_new("assets/test.png");
	suzanne = StModel_new("assets/suzanne.glb");
}

static void update_game(void)
{
	f64 dt = st_window_get_delta_time();
	rot = (StVec3){
		.x = rot.x + (100 * dt),
		.y = rot.y + (100 * dt),
		.z = rot.z + (100 * dt),
	};

	// st_draw_texture_ext(
	// 	m,
	// 	(StVec2){0, 0},
	// 	(StVec2){m->width, m->height},
	// 	(StVec2){0, 0},
	// 	(StVec2){m->width, m->height},
	// 	(StVec2){0, 0}, 0, ST_WHITE
	// );

	st_draw_object_3d((StObject3D){
		.model = suzanne,
		.position = (StVec3){0, 0, 0},
		.rotation = rot,
		.scale = (StVec3){2, 1, 1},
		.tint = st_rgb(255, 255, 255),
	});

	//nk_label(st_ui_ctx(), "Sigma sigma on the wall", NK_TEXT_ALIGN_LEFT);
}

static void free_game(void)
{
	printf("adios\n");
}

int main(int argc, const char* argv[])
{
	i64 sigma = 69;
	i64 sigmas = 420;
	i64 sk = 682862;
	StStack* huh = StStack_new();
	StStack_push(huh, &sigma);
	StStack_push(huh, &sigmas);
	StStack_push(huh, &sk);
	while (huh->length != 0) {
		printf("%li\n", *(i64*)StStack_pop(huh));
	}
	StStack_free(huh);

	st_window_new("Stellarthing", (StVec2i){640, 480});
	st_window_toggle_fullscreen();
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
		// TODO: anything that uses ui would go here
		st_late_update_ui();

		update_game();

		st_end_drawing();
	}

	free_game();

	st_free_ui();
	st_free_lighting();
	st_free_models();
	st_free_textures();
	st_free_input();
	st_window_free();
	return 0;
}
