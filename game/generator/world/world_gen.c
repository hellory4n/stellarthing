#include <FastNoiseLite.h>
#include "world_gen.h"

f64 st_gen_get_block_height(i64 seed, i64 x, i64 z)
{
	fnl_state noise = fnlCreateState();
	noise.seed = seed;
	noise.noise_type = FNL_NOISE_PERLIN;
	noise.fractal_type = FNL_FRACTAL_FBM;
	noise.octaves = 4;
	noise.lacunarity = 2.1676353;

	f64 height = fnlGetNoise2D(&noise, x, z);
	return height;
}