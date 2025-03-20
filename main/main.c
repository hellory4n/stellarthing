#include "core/math/color.h"
#include "core/math/vec.h"
#include "platform/graphics/texture.h"
#include "platform/window.h"
#include "platform/graphics/graphics.h"
#include "platform/input.h"

int main(int argc, char const *argv[])
{
	st_window_new("Stellarthing", (StVec2i){640, 480});
	st_window_toggle_fullscreen();
	__st_init_input();
	__st_init_textures__();

	// mate
	st_add_keymap("test_move", ST_KEY_SPACE);
	st_add_keymap("test_move", ST_KEY_NUM6);
	st_add_keymap("test_move", ST_KEY_J);

	StTexture* m = StTexture_new("assets/test.png");
	StVec2 pos = {40, 60};
	f64 rot = 0;
	StColor color = ST_WHITE;
	StVec3 sndpos = {0.1, 0.1, 0.1};

	while (!st_window_closing()) {
		st_clear(st_rgb(9, 154, 206));

		st_draw_texture_ext(
			m, (StVec2){0, 0}, (StVec2){m->width, m->height}, pos, (StVec2){m->width, m->height},
			(StVec2){0.5, 0.5}, rot, color
		);

		st_end_drawing();
	}

	__st_free_textures__();
	__st_free_input();
	st_window_free();
	return 0;
}
