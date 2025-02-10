#pragma once
#include "core/math/stcolor.h"
#include "core/vectors.h"
#include "texture.h"

void __st_init_graphics__();

void __st_free_graphics__();

/// clears the screen
void StGraphics_clear(stcolor color);

/// ends drawing
void StGraphics_end_drawing();

/// draws texture. rotation is in degrees.
void StGraphics_draw_texture(StTexture* texture, stvec2 pos, float32 rotation);

/// extended drawing texture. src allows cropping the image, dst is the final position and size, rotation is in degrees, and tint changes the color (use white so it doesn't change color)
void StGraphics_draw_texture_ext(StTexture* texture, stvec2 srcPos, stvec2 srcSize, stvec2 dstPos,
    stvec2 dstSize, float32 rotation, stcolor tint);