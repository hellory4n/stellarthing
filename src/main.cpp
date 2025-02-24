#include <stdio.h>
#include "core/vectors.hpp"
#include "core/ref.hpp"
#include "core/collections/array.hpp"
//#include "modules/platform/window.hpp"
//#include "modules/graphics/graphics.hpp"

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
    /*window::open("Stellarthing", Vec2i(640, 480));
    window::toggle_fullscreen();
    window::set_target_fps(144);

    // this will eventually not have tests
    //auto bob = Texture("assets/bob_guy.png");*/

    auto man = Array<char>(6);
    *man.at(0) = 'h';
    *man.at(1) = 'e';
    *man.at(2) = 'l';
    *man.at(3) = 'l';
    *man.at(4) = 'o';
    *man.at(5) = '\0';
    printf("%s\n", man.get_buffer());
}

void __update_modules()
{
    // this will eventually not have tests
    /*graphics::clear(ST_COLOR_WHITE);

    graphics::end_drawing();
    window::update();*/
}

void __free_modules()
{
    //window::close();
}

int main(int argc, char const *argv[])
{
    __init_modules();
    //while (!window::closing()) {
        __update_modules();
    //}
    __free_modules();
    return 0;
}