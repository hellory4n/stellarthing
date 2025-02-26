#include <raylib.h>
#include "graphics.hpp"

namespace starry {

void graphics::clear(Color color)
{
    BeginDrawing();
    ClearBackground({ color.r, color.g, color.b, color.a });
}

void graphics::end_drawing()
{
    EndDrawing();
}

void graphics::draw_texture(Texture texture, Vec2 pos, float32 angle)
{
    graphics::draw_texture_ext(
        texture,
        Vec2(0, 0),
        Vec2(texture.size.x, texture.size.y),
        pos,
        Vec2(texture.size.x, texture.size.y),
        Vec2(0.5, 0.5),
        angle,
        ST_COLOR_WHITE
    );
}

void graphics::draw_texture_ext(Texture texture, Vec2 src_pos, Vec2 src_size, Vec2 dst_pos,
    Vec2 dst_size, Vec2 origin, float32 rotation, Color tint)
{
    // akson dendryt
    DrawTexturePro(
        {
            texture.__data.id,
            texture.__data.width,
            texture.__data.height,
            texture.__data.mipmaps,
            texture.__data.format,
        },
        {(float)src_pos.x, (float)src_pos.y, (float)src_size.x, (float)src_size.y},
        {(float)dst_pos.x, (float)dst_pos.y, (float)dst_size.x, (float)dst_size.y},
        {(float)origin.x * (float)dst_size.x, (float)origin.y * (float)dst_size.y},
        rotation,
        {tint.r, tint.g, tint.b, tint.a}
    );
}

}