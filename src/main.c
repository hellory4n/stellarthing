#include "core/starry.h"
#include "modules/platform/window.h"
#include "modules/graphics/graphics.h"
#include "modules/platform/input.h"

int main(int argc, char const *argv[])
{
    st_new();
    StWindow_create("Stellarthing", (stvec2i){ 640, 480 });
    StWindow_set_fullscreen(true);
    StWindow_set_target_fps(144);

    // mate
    StInput_add_keymap("test_move", ST_KEY_SPACE);
    StInput_add_keymap("test_move", ST_KEY_NUM6);
    StInput_add_keymap("test_move", ST_KEY_J);

    StTexture* m = StTexture_new("assets/test.png");
    stvec2 pos = (stvec2){ 40, 60 };

    while (!StWindow_closing()) {
        if (StInput_is_keymap_held("test_move")) {
            pos.x += 30 * StWindow_get_delta_time();
        }

        StGraphics_clear(ST_WHITE);

        StGraphics_draw_texture(m, pos, 65);

        StGraphics_end_drawing();
        StWindow_update();
    }

    StWindow_free();
    return 0;
}
