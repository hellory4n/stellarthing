#include <raylib.h>
#include "graphics.h"

void StGraphics_clear(stcolor color)
{
    BeginDrawing();
    ClearBackground((Color){ .r = color.r, .g = color.g, .b = color.b, .a = color.a });
}

void StGraphics_end_drawing()
{
    EndDrawing();
}

void StGraphics_draw_texture(StTexture* texture, stvec2 pos, float32 rotation)
{
    // convert texture
    Texture2D textur = {
        .id = texture->id,
        .width = texture->width,
        .height = texture->height,
        .format = texture->format,
        .mipmaps = texture->mipmaps,
    };
    DrawTextureEx(textur, (Vector2){ .x = pos.x, .y = pos.y }, rotation, 1, WHITE);
}

void StGraphics_draw_texture_ext(StTexture* texture, stvec2 srcPos, stvec2 srcSize, stvec2 dstPos,
    stvec2 dstSize, float32 rotation, stcolor tint)
{
    // its late
}