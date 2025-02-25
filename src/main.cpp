#include <stdio.h>
#include "core/string.hpp"
#include "modules/graphics/texture.hpp"
#include "modules/platform/window.hpp"
#include "modules/graphics/graphics.hpp"

// i'm sorry... i'm sorry... i'm sorry...
using namespace starry;

Texture* bob;

void __init_modules()
{
    window::open("Stellarthing", Vec2i(640, 480));
    window::toggle_fullscreen();
    window::set_target_fps(144);

    // this will eventually not have tests
    bob = new Texture("assets/bob_guy.png");

    String hi = "太陽が漏れている。";
    // usually you can just pass the string but it's explicit in printf so clang is happy
    printf("%s\n", hi.cstr());
    String fmt = String::fmt(256, "Fuck %i off", 69);
    printf("%s\n", fmt.cstr());
}

void __update_modules()
{
    // this will eventually not have tests
    graphics::clear(ST_COLOR_WHITE);

    graphics::draw_texture(*bob, Vec2(69, 420), 69);

    graphics::end_drawing();
    window::update();
}

void __free_modules()
{
    delete bob;
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