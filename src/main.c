#include "modules/platform/window.h"
#include "modules/graphics/graphics.h"

int main(int argc, char const *argv[])
{
    StWindow_create("Stellarthing", stvec2i_new(640, 480));
    StWindow_set_fullscreen(true);
    StWindow_set_target_fps(144);

    StTexture* m = StTexture_new("assets/test.png");

    while (!StWindow_closing()) {
        StGraphics_clear(ST_WHITE);

        StGraphics_draw_texture(m, stvec2_new(40, 60), 65);

        StGraphics_end_drawing();
        StWindow_update();
    }

    StWindow_free();
    return 0;
}
