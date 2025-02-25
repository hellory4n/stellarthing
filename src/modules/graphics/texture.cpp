#include <stdio.h>
#include <raylib.hpp>
#include "texture.hpp"

namespace starry {

Texture::Texture(String path)
{
    rl::Texture2D t = rl::LoadTexture(path);
    this->__internal = {
        .id = t.id,
        .width = t.width,
        .height = t.height,
        .mipmaps = t.mipmaps,
        .format = t.format,
    };
    printf("[ASSETS] Loaded texture at %s\n", (char*)path);
}

Texture::Texture()
{
    this->__internal = {
        .id = 0,
        .width = 0,
        .height = 0,
        .mipmaps = 0,
        .format = 0,
    };
}

Texture::~Texture()
{
    rl::Texture2D t = {
        .id = this->__internal.id,
        .width = this->__internal.width,
        .height = this->__internal.height,
        .mipmaps = this->__internal.mipmaps,
        .format = this->__internal.format,
    };
    rl::UnloadTexture(t);
}

Vec2i Texture::size()
{
    return Vec2i(this->__internal.width, this->__internal.height);
}

}