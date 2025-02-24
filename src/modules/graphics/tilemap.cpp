#include <stdio.h>
#include <math.h>
#include "graphics.hpp"
#include "tilemap.hpp"

namespace starry {

TileWorld::TileWorld()
{
    printf("[WORLD] New world created\n");
}

TileWorld::~TileWorld()
{
    printf("[WORLD] I WANT TO BREAK FREE\n");
}

Tile* TileWorld::get_tile(vec3 pos, bool ground)
{
    // :(
    Tile* lasigm;
    if (ground) {
        lasigm = &(this->ground[(int64)floor(pos.x)][(int64)floor(pos.y)])[(int64)floor(pos.z + (-ST_MIN_LAYER))];
    }
    else {
        lasigm = &(this->objects[(int64)floor(pos.x)][(int64)floor(pos.y)])[(int64)floor(pos.z + (-ST_MIN_LAYER))];
    }

    // if it's a new tile then make it not suck
    if (lasigm->textures[0]->__internal.id == 0) {
        lasigm->position = pos;
        lasigm->tint = ST_COLOR_WHITE;
    }

    return lasigm;
}

void TileWorld::__draw_chunk(vec2i offset)
{
    for (int64 y = this->current_chunk.y + offset.y; y < this->current_chunk.y + offset.y + ST_CHUNK_SIZE; y++) {
        for (int64 x = this->current_chunk.x + offset.x; x < this->current_chunk.x + offset.x + ST_CHUNK_SIZE; x++) {
            Tile tile = this->ground[x][y][this->current_layer];
            vec2 transformed_pos =
                vec2(tile.position.x, tile.position.y) + this->camera_position
                * (vec2)tile.textures[tile.side]->size()
                * this->camera_scale;
            
            graphics::draw_texture_ext(
                *tile.textures[tile.side],
                vec2(0, 0),
                (vec2)tile.textures[tile.side]->size(),
                transformed_pos,
                (vec2)tile.textures[tile.side]->size() * this->camera_scale,
                vec2(0, 0), 0, tile.tint
            );
        }
    }
}

void TileWorld::draw()
{
    this->__draw_chunk(vec2i(-1, -1));
    this->__draw_chunk(vec2i( 0, -1));
    this->__draw_chunk(vec2i( 1, -1));
    this->__draw_chunk(vec2i(-1,  0));
    this->__draw_chunk(vec2i( 0,  0));
    this->__draw_chunk(vec2i( 1,  0));
    this->__draw_chunk(vec2i(-1,  1));
    this->__draw_chunk(vec2i( 0,  1));
    this->__draw_chunk(vec2i( 1,  1));
}

}