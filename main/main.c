#include "core/math/color.h"
#include "core/math/vec.h"
#include "platform/graphics/model.h"
#include "platform/graphics/texture.h"
#include "platform/window.h"
#include "platform/graphics/graphics.h"
#include "platform/input.h"
#include <stdio.h>

StTexture* m;
StModel* suzanne;

static void init_game(void)
{
	st_set_camera((StCamera){
		.position = (StVec3){0.5, 0.5, 5},
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
	st_clear(ST_BLACK);
	// before the 2d stuff because 2d is used for ui stuff
	st_draw_all_3d_objects();

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
		.rotation = (StVec3){7, 15, 62},
		.scale = (StVec3){2, 1, 1},
		.tint = st_rgb(255, 255, 255),
	});

	st_end_drawing();
}

static void free_game(void)
{
	printf("adios\n");
}

int main(int argc, char const *argv[])
{
	st_window_new("Stellarthing", (StVec2i){640, 480});
	st_window_toggle_fullscreen();
	__st_init_input();
	__st_init_textures();
	__st_init_models();

	init_game();

	while (!st_window_closing()) {
		update_game();
	}

	free_game();

	__st_free_models();
	__st_free_textures();
	__st_free_input();
	st_window_free();
	return 0;
}
