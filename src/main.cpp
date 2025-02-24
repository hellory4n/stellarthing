#include <stdio.h>
#include "core/vectors.hpp"
#include "modules/platform/window.hpp"
#include "modules/graphics/graphics.hpp"
#include "modules/graphics/tilemap.hpp"

// i'm sorry... i'm sorry... i'm sorry...
using namespace starry;

TileWorld* world;

void __init_modules()
{
    window::open("Stellarthing", vec2i(640, 480));
    window::toggle_fullscreen();
    window::set_target_fps(144);

    // this will eventually not have tests
    auto bob = Texture("assets/bob_guy.png");

    world = new TileWorld();
    
    Tile* tile = world->get_tile(vec3(3, 3, 0), false);
    tile->textures[0] = &bob;

    Tile* til = world->get_tile(vec3(4, 3, 0), false);
    til->textures[0] = &bob;

    Tile* ti = world->get_tile(vec3(5, 3, 0), false);
    ti->textures[0] = &bob;

    Tile* t = world->get_tile(vec3(6, 3, 0), false);
    t->textures[0] = &bob;
}

void __update_modules()
{
    // this will eventually not have tests
    graphics::clear(ST_COLOR_WHITE);

    world->draw();

    graphics::end_drawing();
    window::update();
}

void __free_modules()
{
    // cant be bothered
    // im gonna add a ref counter soon
    //oimate.free();
    delete world;
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