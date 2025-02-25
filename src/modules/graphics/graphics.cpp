#include "raylib.hpp"
#include "graphics.hpp"

namespace starry {

void graphics::clear(Color Color)
{
    rl::BeginDrawing();
    rl::ClearBackground((rl::Color){ .r = Color.r, .g = Color.g, .b = Color.b, .a = Color.a });
}

void graphics::end_drawing()
{
    rl::EndDrawing();
}

void graphics::draw_texture(Texture texture, Vec2 pos, float32 angle)
{
    graphics::draw_texture_ext(
        texture,
        Vec2(0, 0),
        Vec2(texture.size().x, texture.size().y),
        pos,
        Vec2(texture.size().x, texture.size().y),
        Vec2(0.5, 0.5),
        angle,
        ST_COLOR_WHITE
    );
}

void graphics::draw_texture_ext(Texture texture, Vec2 src_pos, Vec2 src_size, Vec2 dst_pos,
    Vec2 dst_size, Vec2 origin, float32 rotation, Color tint)
{
    // akson dendryt
    rl::DrawTexturePro(
        texture.__internal,
        (rl::Rectangle){(float)src_pos.x, (float)src_pos.y, (float)src_size.x, (float)src_size.y},
        (rl::Rectangle){(float)dst_pos.x, (float)dst_pos.y, (float)dst_size.x, (float)dst_size.y},
        (rl::Vector2){(float)origin.x * (float)dst_size.x, (float)origin.y * (float)dst_size.y},
        rotation,
        (rl::Color){tint.r, tint.g, tint.b, tint.a}
    );
}

}