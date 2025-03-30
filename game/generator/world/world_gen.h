#pragma once
#include "core/core.h"
#include "core/math/color.h"

#ifndef ST_GEN_BASE_HEIGHT
#define ST_GEN_BASE_HEIGHT 64
#endif

#ifndef ST_GEN_CHUNK_SIZE
/// it's a really tall cube
#define ST_GEN_CHUNK_SIZE 16
#endif

// sigma
typedef struct {
	f32 height;
	StColor color;
} StTerrainPart;

/// Returns a 2d array at the specified chunk. Remember to free the array after using it
StTerrainPart* st_gen_chunk(i64 seed, i64 chunk_x, i64 chunk_z);

/// range is -0.5 to 0.5 i think??
StColor st_gen_get_color(f64 height);

/// Generates a chunk mesh from the output of `st_gen_chunk`
//void* st_gen_chunk_mesh(StTerrainPart* chunk);
