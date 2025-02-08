#pragma once

/// texture :)
typedef struct {
    /// i'm legally prohibited from including raylib in header files it's complicated
    void* internal;
} StTexture;

void __st_init_textures__();

void __st_free_textures__();

/// loads a texture from a path
StTexture StTexture_new(const char* path);

/// frees the texture
void StTexture_free(StTexture* t);