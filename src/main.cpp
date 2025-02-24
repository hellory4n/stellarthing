#include <stdio.h>
#include "core/vectors.hpp"
#include "core/ref.hpp"
#include "modules/platform/window.hpp"
#include "modules/graphics/graphics.hpp"

// i'm sorry... i'm sorry... i'm sorry...
using namespace starry;

class ShittyClass {
public:
    int64 fuckoff = 69;

    ShittyClass()
    {
        printf("hi mom\n");
    }

    ~ShittyClass()
    {
        printf("rip :(\n");
    }
};

void __init_modules()
{
    window::open("Stellarthing", Vec2i(640, 480));
    window::toggle_fullscreen();
    window::set_target_fps(144);

    // this will eventually not have tests
    //auto bob = Texture("assets/bob_guy.png");

    auto ref = newref<ShittyClass>();
    printf("refs %li\n", ref.get_ref_count());
    printf("fuckoff %li\n", ref->fuckoff);

    auto ref2 = newref<ShittyClass>(ref);
    printf("refs %li\n", ref2.get_ref_count());
    printf("fuckoff %li\n", ref2->fuckoff);
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