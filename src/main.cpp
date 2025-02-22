#include <stdio.h>
#include "core/vectors.hpp"
#include "modules/platform/window.hpp"
#include "modules/graphics/graphics.hpp"

int main(int argc, char const *argv[])
{
    // cant be bothered
    using namespace starry;

    window::open("Stellarthing", vec2i(640, 480));
    window::toggle_fullscreen();
    window::set_target_fps(144);

    Texture oimate = Texture("assets/bob_guy.png");

    while (!window::closing()) {
        graphics::clear(ST_COLOR_WHITE);

        graphics::draw_texture(oimate, vec2(60, 60), 65);

        graphics::end_drawing();
        window::update();
    }

    oimate.free();

    window::close();
    return 0;
}
