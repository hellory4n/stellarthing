#ifndef ST_GRAPHICS_H
#define ST_GRAPHICS_H
#include <raylib.h>
#include <libtrippin.h>

// didn't feel like using a dynamic array
#define ST_MAX_3D_OBJECTS 1024

#define ST_2D_RENDER_WIDTH 1280
#define ST_2D_RENDER_HEIGHT 720

// so 1, 1, 1 is actually 16 voxels :D
#define ST_VOXEL_SIZE 16

// As the name implies, it's an object, in 3D.
typedef struct {
	Model model;
	TrVec3f position;
	// Rotation in euler degrees
	TrVec3f rotation;
	/// It's a multiplier so (1, 1, 1) is the original size
	TrVec3f scale;
	TrColor tint;
} Object3D;

void graphics_init(void);

void graphics_free(void);

void graphics_begin_2d(void);

void graphics_end_2d(void);

void graphics_draw_all_3d_objects(void);

void graphics_set_camera(Camera3D cam);

Camera3D graphics_camera(void);

// yea
void graphics_draw_3d_obj(Object3D obj);

#endif // ST_GRAPHICS_H
