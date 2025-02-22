#ifndef ST_TEXTURE_H
#define ST_TEXTURE_H
#include "core/core.hpp"

namespace starry {

/// texture :)
class Texture {
public:
    uint32 id;
    int32 width;
    int32 height;
    int32 mipmaps;
    int32 format;

    Texture(const char* path);
    ~Texture();

    static void __init_subsystem();
    static void __free_subsystem();
};

}

#endif // ST_TEXTURE_H
