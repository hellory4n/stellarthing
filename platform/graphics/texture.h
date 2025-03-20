#pragma once
#include "core/core.h"

/// Texture :) this maps directly to a raylib texture
typedef struct {
	u32 id;
	i32 width;
	i32 height;
	i32 mipmaps;
	i32 format;
} StTexture;

void __st_init_textures__(void);

void __st_free_textures__(void);

/// Loads a texture from a path. supported formats are PNG, BMP, TGA, JPG, GIF, QOI, PSD, DDS, HDR, KTX,
/// ASTC, PKM, and PVR
StTexture* StTexture_new(const char* path);

/// Frees the texture
void StTexture_free(StTexture* t);