#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include "core/collections/array.hpp"
#include "core/collections/hashmap.hpp"
#include "core/math/color.hpp"
#include "core/math/math.hpp"
#include "graphics.hpp"
#include "tilemap.hpp"

namespace starry {

Ref<Texture> Tile::get_texture()
{
    switch (this->side) {
        case 0: return this->texture0;
        case 1: return this->texture1;
        case 2: return this->texture2;
        case 3: return this->texture3;
        default:
            fprintf(stderr, "[TILEMAP] YOU IDIOT THE SIDE HAS TO BE 0-3");
            fflush(stderr);
            assert(false);
            break;
    }
}

TileWorld::TileWorld(Vec2i min_chunk, Vec2i max_chunk)
{
    // this may be one of the worst things ive ever done
    this->ground = HashMap<Vec2i, Array<Array<Tile>*>*>();
    for (int64 y = min_chunk.y; y < max_chunk.y; y++) {
        for (int64 x = min_chunk.x; x < max_chunk.x; x++) {
            auto* man = new Array<Array<Tile>*>(ST_TOTAL_LAYERS);
            
            for (nint i = 0; i < man->length; i++) {
                auto* manman = new Array<Tile>(ST_CHUNK_SIZE * ST_CHUNK_SIZE);

                for (nint j = 0; j < manman->length; j++) {
                    *manman->at(j) = (Tile){
                        .position = Vec3(0, 0, 0),
                        .tint = ST_COLOR_WHITE,
                        .side = 0,
                        .empty = true,
                        .texture0 = {0},
                        .texture1 = {0},
                        .texture2 = {0},
                        .texture3 = {0},
                    };
                }

                *man->at(i) = manman;
            }

            this->ground.set(Vec2i(x, y), man);
        }
    }
    
    // i should try rust
    this->objects = HashMap<Vec2i, Array<Array<Tile>*>*>();
    for (int64 y = min_chunk.y; y < max_chunk.y; y++) {
        for (int64 x = min_chunk.x; x < max_chunk.x; x++) {
            auto* man = new Array<Array<Tile>*>(ST_TOTAL_LAYERS);
            
            for (nint i = 0; i < man->length; i++) {
                auto* manman = new Array<Tile>(ST_CHUNK_SIZE * ST_CHUNK_SIZE);

                for (nint j = 0; j < manman->length; j++) {
                    *manman->at(j) = Tile {
                        .position = Vec3(0, 0, 0),
                        .tint = ST_COLOR_WHITE,
                        .side = 0,
                        .empty = true,
                        .texture0 = {0},
                        .texture1 = {0},
                        .texture2 = {0},
                        .texture3 = {0},
                    };
                }

                *man->at(i) = manman;
            }

            this->objects.set(Vec2i(x, y), man);
        }
    }

    printf("[WORLD] New world created\n");
}

TileWorld::~TileWorld()
{
    printf("[WORLD] I WANT TO BREAK FREE\n");
}

Tile* TileWorld::get_tile(Vec3 pos, bool ground)
{
    Array<Array<Tile>*>** chunk;
    if (ground) {
        chunk = this->ground.get(
            Vec2i((int64)floor(pos.x / ST_CHUNK_SIZE), (int64)floor(pos.y / ST_CHUNK_SIZE))
        );
    }
    else {
        chunk = this->objects.get(
            Vec2i((int64)floor(pos.x / ST_CHUNK_SIZE), (int64)floor(pos.y / ST_CHUNK_SIZE))
        );
    }
    assert(chunk != nullptr);

    nint offsetted = clamp(round(pos.z) + -ST_MIN_LAYER, ST_MIN_LAYER, ST_MAX_LAYER);
    Array<Tile>* layer = *(*chunk)->at(offsetted);
    assert(layer != nullptr);

    return layer->at2d((uint64)floor(pos.x), (uint64)floor(pos.y), ST_CHUNK_SIZE);
}

Tile* TileWorld::add_tile(Vec3 pos, bool ground, Ref<Texture> side0, Ref<Texture> side1, Ref<Texture> side2, Ref<Texture> side3)
{
    Tile* tile = this->get_tile(pos, ground);
    assert(tile != nullptr);

    if (!tile->empty) return tile;

    tile->empty = false;
    tile->position = pos;
    tile->texture0 = side0;
    tile->texture1 = side1;
    tile->texture2 = side2;
    tile->texture3 = side3;
    return tile;
}

void TileWorld::__draw_chunk(Vec2i offset)
{
    for (int64 y = this->current_chunk.y + offset.y; y < this->current_chunk.y + offset.y + ST_CHUNK_SIZE; y++) {
        for (int64 x = this->current_chunk.x + offset.x; x < this->current_chunk.x + offset.x + ST_CHUNK_SIZE; x++) {
            // render ground tiles
            Tile* tile = this->get_tile(Vec3(x, y, this->current_layer), true);
            Vec2 transformed_pos =
                Vec2(tile->position.x, tile->position.y) + this->camera_position
                * (Vec2)tile->get_texture()->size
                * this->camera_scale;
            
            graphics::draw_texture_ext(
                **tile->get_texture(),
                Vec2(0, 0),
                (Vec2)tile->get_texture()->size,
                transformed_pos,
                (Vec2)tile->get_texture()->size * this->camera_scale,
                Vec2(0, 0), 0, tile->tint
            );

            // render object tiles
            Tile* tile2 = this->get_tile(Vec3(x, y, this->current_layer), false);
            Vec2 transformed_po =
                Vec2(tile2->position.x, tile2->position.y) + this->camera_position
                * (Vec2)tile->get_texture()->size
                * this->camera_scale;
            
            graphics::draw_texture_ext(
                **tile->get_texture(),
                Vec2(0, 0),
                (Vec2)tile->get_texture()->size,
                transformed_po,
                (Vec2)tile->get_texture()->size * this->camera_scale,
                Vec2(0, 0), 0, tile2->tint
            );
        }
    }
}

void TileWorld::draw()
{
    this->__draw_chunk(Vec2i(-1, -1));
    this->__draw_chunk(Vec2i( 0, -1));
    this->__draw_chunk(Vec2i( 1, -1));
    this->__draw_chunk(Vec2i(-1,  0));
    this->__draw_chunk(Vec2i( 0,  0));
    this->__draw_chunk(Vec2i( 1,  0));
    this->__draw_chunk(Vec2i(-1,  1));
    this->__draw_chunk(Vec2i( 0,  1));
    this->__draw_chunk(Vec2i( 1,  1));
}

}