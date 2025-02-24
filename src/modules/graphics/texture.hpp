#ifndef ST_TEXTURE_H
#define ST_TEXTURE_H
#include "raylib.hpp"
#include "core/core.hpp"
#include "core/vectors.hpp"

namespace starry {

/// texture :)
class Texture {
public:
    rl::Texture2D __internal;

    Texture(const char* path);
    
    /// frees the stuff
    void free();

    /// returns the size of the texture
    Vec2i size();
};

}

#endif // ST_TEXTURE_H
