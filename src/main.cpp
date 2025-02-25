#include <stdio.h>
#include "modules/platform/window.hpp"
#include "modules/graphics/graphics.hpp"

// i'm sorry... i'm sorry... i'm sorry...
using namespace starry;

void __init_modules()
{
    window::open("Stellarthing", Vec2i(640, 480));
    window::toggle_fullscreen();
    window::set_target_fps(144);

    // this will eventually not have tests
    //auto bob = Texture("assets/bob_guy.png");

    /*String hi = String("hello", 6);
    printf("%s\n", hi.cstr());
    String fmt = String::fmt(256, "Fuck %i off", 69);
    printf("%s\n", fmt.cstr());*/
}

void __update_modules()
{
    // this will eventually not have tests
    graphics::clear(ST_COLOR_WHITE);

    graphics::end_drawing();
    window::update();
}

void __free_modules()
{
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