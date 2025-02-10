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

/// @brief extended draw texture
/// @param texture it's a texture
/// @param srcPos used for cropping the texture
/// @param srcSize used for cropping the texture
/// @param dstPos the actual position of the texture
/// @param dstSize the actual size of the texture
/// @param origin origin point. (0, 0) is the top left, (0.5, 0.5) is the center, and (1, 1) is the bottom right
/// @param rotation rotation in degrees
/// @param tint changes the color of the texture.
void StGraphics_draw_texture_ext(StTexture* texture, stvec2 srcPos, stvec2 srcSize, stvec2 dstPos,
    stvec2 dstSize, stvec2 origin, float32 rotation, stcolor tint);