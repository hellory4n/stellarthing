#include "core/ref.hpp"
#include "core/string.hpp"
#include "modules/graphics/texture.hpp"
#include "modules/platform/window.hpp"
#include "modules/graphics/graphics.hpp"

// i'm sorry... i'm sorry... i'm sorry...
using namespace starry;

Ref<Texture> bob = {0};

void __init_modules()
{
    window::open("Stellarthing", Vec2i(640, 480));
    window::toggle_fullscreen();
    window::set_target_fps(144);
    Texture::__init_subsystem();

    // this will eventually not have tests
    bob = Texture::load("assets/bob_guy.png");
}

void __update_modules()
{
    // this will eventually not have tests
    graphics::clear(ST_COLOR_WHITE);

    graphics::draw_texture(**bob, Vec2(69, 420), 69);

    graphics::end_drawing();
    window::update();
}

void __free_modules()
{
    Texture::__free_subsystem();
    window::close();
}

int main(int argc, char const *argv[])
{
    __init_modules();
    while (!window::closing()) {
        __update_modules();
    }
    __free_modules();
    return 0;
}