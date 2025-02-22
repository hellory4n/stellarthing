#ifndef ST_GRAPHICS_H
#define ST_GRAPHICS_H
#include "core/math/color.hpp"
#include "core/vectors.hpp"
#include "texture.hpp"

namespace starry {

/// why see when you can C++
namespace graphics {
    /// clears the screen
    void clear(color col);

    /// end drawing
    void end_drawing();

    /// draw texutre :)
    void draw_texture(Texture texture, vec2 pos, float32 angle);

    /// @brief extended draw texture
    /// @param texture it's a texture
    /// @param srcPos used for cropping the texture
    /// @param srcSize used for cropping the texture
    /// @param dstPos the actual position of the texture
    /// @param dstSize the actual size of the texture
    /// @param origin origin point. (0, 0) is the top left, (0.5, 0.5) is the center, and (1, 1) is the bottom right
    /// @param rotation rotation in degrees
    /// @param tint changes the color of the texture.
    void draw_texture_ext(Texture texture, vec2 srcPos, vec2 srcSize, vec2 dstPos, vec2 dstSize,
        vec2 origin, float32 rotation, color tint);
}

}

#endif // ST_GRAPHICS_H
