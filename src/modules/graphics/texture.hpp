#ifndef ST_TEXTURE_H
#define ST_TEXTURE_H
#include "core/math/vec2i.hpp"
#include "core/ref.hpp"
#include "core/string.hpp"

namespace starry {

/// its a texture
class Texture {
public:
    /// raylib texture thingy
    struct __RlTexture {
        uint32 id;
        int32 width;
        int32 height;
        int32 mipmaps;
        int32 format;
    };
    __RlTexture __data;

    /// the path to the texture
    //String path;
    /// the size of the texture
    Vec2i size;

    static void __init_subsystem();

    static void __free_subsystem();

    /// loads a texture
    static Ref<Texture> load(String path);

    /// forces the texture to be removed from its cache
    static void force_free(Ref<Texture> texture);
};

}

#endif // ST_TEXTURE_H
