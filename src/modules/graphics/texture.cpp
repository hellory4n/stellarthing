#include <stdio.h>
#include "core/collections/hashmap.hpp"
#include "texture.hpp"

namespace starry {

Texture::Texture(const char* path)
{
    this->__internal = rl::LoadTexture(path);
    printf("[ASSETS] Loaded texture at %s\n", path);
}

void Texture::free()
{
    rl::UnloadTexture(this->__internal);
}

vec2i Texture::size()
{
    return vec2i(this->__internal.height, this->__internal.height);
}

}