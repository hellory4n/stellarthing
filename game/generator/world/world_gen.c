#include <FastNoiseLite.h>
#include "world_gen.h"

i64 st_gen_get_block_height(i64 seed, i64 x, i64 z)
{
	fnl_state noise = fnlCreateState();
	noise.seed = seed;
	noise.noise_type = FNL_NOISE_PERLIN;

	f64 height = ST_GEN_BASE_HEIGHT + fnlGetNoise2D(&noise, x, z) * 20;
	return (i64)height;
}