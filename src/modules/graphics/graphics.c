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
    StGraphics_draw_texture_ext(
        texture,
        STVEC2_ZERO,
        (stvec2){ texture->width, texture->height },
        pos,
        (stvec2){ texture->width, texture->height },
        (stvec2){ 0.5, 0.5 },
        rotation,
        ST_WHITE
    );
}

void StGraphics_draw_texture_ext(StTexture* texture, stvec2 srcPos, stvec2 srcSize, stvec2 dstPos,
    stvec2 dstSize, stvec2 origin, float32 rotation, stcolor tint)
{
    // akson dendryt
    DrawTexturePro(
        (Texture2D){
            .id = texture->id,
            .width = texture->width,
            .height = texture->height,
            .format = texture->format,
            .mipmaps = texture->mipmaps,
        },
        (Rectangle){ .x = srcPos.x, .y = srcPos.y, .width = srcSize.x, .height = srcSize.y },
        (Rectangle){ .x = dstPos.x, .y = dstPos.y, .width = dstSize.x, .height = dstSize.y },
        (Vector2){ .x = origin.x * dstSize.x, .y = origin.y * dstSize.y },
        rotation,
        (Color){ .r = tint.r, .g = tint.g, .b = tint.b, .a = tint.a }
    );
}