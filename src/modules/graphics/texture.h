#pragma once
#include "core/core.h"
#include "core/vectors.h"

/// texture :) this maps directly to a raylib texture
typedef struct {
    uint32 id;
    int32 width;
    int32 height;
    int32 mipmaps;
    int32 format;
} StTexture;

void __st_init_textures__();

void __st_free_textures__();

/// loads a texture from a path
StTexture* StTexture_new(const char* path);

/// frees the texture
void StTexture_free(StTexture* t);