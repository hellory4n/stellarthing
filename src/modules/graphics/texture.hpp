#ifndef ST_TEXTURE_H
#define ST_TEXTURE_H
#include "core/math/vec2i.hpp"
#include "core/string.hpp"

namespace starry {

/// texture :)
class Texture {
private:
public:
    /// exact copy of the raylib texture struct. you probably shouldn't use this directly.
    typedef struct __RlTexture {
        unsigned int id;        // OpenGL texture id
        int width;              // Texture base width
        int height;             // Texture base height
        int mipmaps;            // Mipmap levels, 1 by default
        int format;             // Data format (PixelFormat type)
    } __RlTexture;

    __RlTexture __internal;

    Texture(String path);
    Texture();
    ~Texture();

    /// returns the size of the texture
    Vec2i size();
};

}

#endif // ST_TEXTURE_H
