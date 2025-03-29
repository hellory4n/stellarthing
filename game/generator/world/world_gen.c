#include <FastNoiseLite.h>
#include "world_gen.h"
#include "core/math/color.h"

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

StColor st_gen_get_color(f64 height)
{
	// the range is -1 to 1 except not really??
	StColor color;
	if (height < -0.6 / 2) {
		// dark blue
		color = st_rgb(0, 82, 172);
	}
	else if (height < -0.3 / 2) {
		// blue
		color = st_rgb(0, 121, 241);
	}
	else if (height < -0.1 / 2) {
		// light blue
		color = st_rgb(102, 191, 255);
	}
	else if (height < 0.0) {
		// beige
		color = st_rgb(240, 244, 195);
	}
	else if (height < 0.2 / 2) {
		// light green
		color = st_rgb(0, 228, 48);
	}
	else if (height < 0.4 / 2) {
		// green
		color = st_rgb(0, 158, 47);
	}
	else if (height < 0.6 / 2) {
		// dark green
		color = st_rgb(0, 117, 44);
	}
	else if (height < 0.75 / 2) {
		// gray
		color = st_rgb(96, 130, 145);
	}
	else if (height < 0.9 / 2) {
		color = st_rgb(80, 80, 80);
	}
	else {
		color = st_rgb(255, 255, 255);
	}
	return color;
}