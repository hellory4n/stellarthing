#include "raylib.hpp"
#include "graphics.hpp"

namespace starry {

void graphics::clear(color color)
{
    rl::BeginDrawing();
    rl::ClearBackground((rl::Color){ .r = color.r, .g = color.g, .b = color.b, .a = color.a });
}

void graphics::end_drawing()
{
    rl::EndDrawing();
}

void graphics::draw_texture(Texture texture, vec2 pos, float32 angle)
{
    graphics::draw_texture_ext(
        texture,
        vec2(0, 0),
        vec2(texture.size().x, texture.size().y),
        pos,
        vec2(texture.size().x, texture.size().y),
        vec2(0.5, 0.5),
        angle,
        ST_COLOR_WHITE
    );
}

void graphics::draw_texture_ext(Texture texture, vec2 src_pos, vec2 src_size, vec2 dst_pos,
    vec2 dst_size, vec2 origin, float32 rotation, color tint)
{
    // akson dendryt
    rl::DrawTexturePro(
        texture.__internal,
        (rl::Rectangle){ src_pos.x, src_pos.y, src_size.x, src_size.y },
        (rl::Rectangle){ dst_pos.x, dst_pos.y, dst_size.x, dst_size.y },
        (rl::Vector2){ origin.x * dst_size.x, origin.y * dst_size.y },
        rotation,
        (rl::Color){ tint.r, tint.g, tint.b, tint.a }
    );
}

}