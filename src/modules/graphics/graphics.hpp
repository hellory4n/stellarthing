#ifndef ST_GRAPHICS_H
#define ST_GRAPHICS_H
#include "core/math/color.hpp"
#include "core/vectors.hpp"
#include "texture.hpp"

namespace starry {

/// why see when you can C++
namespace graphics {
    /// clears the screen
    void clear(Color col);

    /// end drawing
    void end_drawing();

    /// draw texutre :)
    void draw_texture(Texture texture, Vec2 pos, float32 angle);

    /// @brief extended draw texture
    /// @param texture it's a texture
    /// @param srcPos used for cropping the texture
    /// @param srcSize used for cropping the texture
    /// @param dstPos the actual position of the texture
    /// @param dstSize the actual size of the texture
    /// @param origin origin point. (0, 0) is the top left, (0.5, 0.5) is the center, and (1, 1) is the bottom right
    /// @param rotation rotation in degrees
    /// @param tint changes the Color of the texture.
    void draw_texture_ext(Texture texture, Vec2 srcPos, Vec2 srcSize, Vec2 dstPos, Vec2 dstSize,
        Vec2 origin, float32 rotation, Color tint);
}

}

#endif // ST_GRAPHICS_H
