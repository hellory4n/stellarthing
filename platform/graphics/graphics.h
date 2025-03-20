#pragma once
#include "core/math/color.h"
#include "core/math/vec.h"
#include "texture.h"

/// Clears the screen
void st_clear(StColor color);

/// Ends drawing
void st_end_drawing(void);

/// Draws texture. If you want to suffer, use `st_draw_texture_ext`
void st_draw_texture(StTexture* texture, StVec2 pos, f64 degrees);

/// @brief Extended draw texture
/// @param texture it's a texture
/// @param src_pos used for cropping the texture
/// @param src_size used for cropping the texture
/// @param dst_pos the actual position of the texture
/// @param dst_size the actual size of the texture
/// @param origin origin point. (0, 0) is the top left, (0.5, 0.5) is the center, and (1, 1) is the bottom right
/// @param degrees rotation in degrees
/// @param tint changes the color of the texture.
void st_draw_texture_ext(StTexture* texture, StVec2 src_pos, StVec2 src_size, StVec2 dst_pos,
	StVec2 dst_size, StVec2 origin, f64 degrees, StColor tint);