#include <stdlib.h>
#include <raylib.h>
#include <FastNoiseLite.h>
#include "world_gen.h"
#include "core/math/color.h"
#include "platform/graphics/model.h"

StTerrainPart* st_gen_chunk(i64 seed, i64 chunk_x, i64 chunk_z)
{
	StTerrainPart* map = malloc(ST_GEN_CHUNK_SIZE * ST_GEN_CHUNK_SIZE * sizeof(StTerrainPart));

	fnl_state noise = fnlCreateState();
	noise.seed = seed;
	noise.noise_type = FNL_NOISE_PERLIN;
	noise.fractal_type = FNL_FRACTAL_FBM;
	noise.octaves = 6;
	noise.lacunarity = 2.1676353;

	nint idx = 0;
	for (i64 z = 0; z < ST_GEN_CHUNK_SIZE; z++) {
		for (i64 x = 0; x < ST_GEN_CHUNK_SIZE; x++) {
			f64 height = fnlGetNoise2D(&noise, x + chunk_x, z + chunk_z);

			map[idx] = (StTerrainPart){
				.height = height,
				.color = st_gen_get_color(height),
			};

			idx++;
		}
	}

	return map;
}

StModel* st_gen_chunk_mesh(StTerrainPart* chunk)
{
	Mesh meshma = {};
	meshma.vertices = malloc(ST_GEN_CHUNK_SIZE * ST_GEN_CHUNK_SIZE * sizeof(float) * 3);
	meshma.vertexCount = ST_GEN_CHUNK_SIZE * ST_GEN_CHUNK_SIZE * 3;

	// add the bloody vertices
	i64 vert_idx = 0;
	i64 heightmap_idx = 0;

	for (i64 z = 0; z < ST_GEN_CHUNK_SIZE; z++) {
		for (i64 x = 0; x < ST_GEN_CHUNK_SIZE; x++) {
			meshma.vertices[vert_idx] = x;
			meshma.vertices[vert_idx + 1] = chunk[heightmap_idx].height;
			meshma.vertices[vert_idx + 2] = z;
			vert_idx += 3;
			heightmap_idx++;
		}
	}

	// add the bloody triangle indices
	i64 quads = (ST_GEN_CHUNK_SIZE - 1) * (ST_GEN_CHUNK_SIZE - 1);
	meshma.indices = malloc(quads * 3 * 2 * sizeof(u16));
	meshma.triangleCount = quads * 2;
	i64 triangles = 0;

	for (i64 z = 0; z < ST_GEN_CHUNK_SIZE; z++) {
		for (i64 x = 0; x < ST_GEN_CHUNK_SIZE; x++) {
			i64 top_left = z * ST_GEN_CHUNK_SIZE + x;
			i64 top_right = top_left + 1;
			i64 bottom_left = (z + 1) * ST_GEN_CHUNK_SIZE + x;
			i64 bottom_right = bottom_left + 1;

			// first triangle
			meshma.indices[triangles] = top_left;
			meshma.indices[triangles + 1] = bottom_left;
			meshma.indices[triangles + 2] = top_right;
			triangles += 3;

			// second triangle
			meshma.indices[triangles] = top_right;
			meshma.indices[triangles + 1] = bottom_left;
			meshma.indices[triangles + 2] = bottom_right;
			triangles += 3;
		}
	}

	UploadMesh(&meshma, false);

	// uy
	Model modeldeez = LoadModelFromMesh(meshma);
	Model* rfuick = malloc(sizeof(StModel));
	*rfuick = modeldeez;
	return (StModel*)rfuick;
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

