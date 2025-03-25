#pragma once
#include "core/math/color.h"
#include "core/math/vec.h"
#include "platform/graphics/model.h"
#include "texture.h"

#ifndef ST_MAX_3D_OBJECTS
#define ST_MAX_3D_OBJECTS 128
#endif

/// It's a camera. Quite important for seeing shit.
typedef struct {
	StVec3 position;
	/// Where the camera is looking at
	StVec3 target;
	/// Field of view
	f64 fov;
	/// Projection, true is perspective and false is orthographic
	bool perspective;
} StCamera;

typedef struct {
	StModel* model;
	StVec3 position;
	// Rotation in euler degrees
	StVec3 rotation;
	/// It's a multiplier so (1, 1, 1) is the original size
	StVec3 scale;
	StColor tint;
} StObject3D;

/// Clears the screen
void st_clear(StColor color);

/// Ends drawing
void st_end_drawing(void);

/// Draws texture. If you want to suffer, use `st_draw_texture_ext`
void st_draw_texture(StTexture* texture, StVec2 pos, f64 degrees);

/// @brief Extended draw texture
/// @param texture it's a texture
/// @param src_pos used for cropping the texture
/// @param src_size used for cropping the texture
/// @param dst_pos the actual position of the texture
/// @param dst_size the actual size of the texture
/// @param origin origin point. (0, 0) is the top left, (0.5, 0.5) is the center, and (1, 1) is the bottom right
/// @param degrees rotation in degrees
/// @param tint changes the color of the texture.
void st_draw_texture_ext(StTexture* texture, StVec2 src_pos, StVec2 src_size, StVec2 dst_pos,
	StVec2 dst_size, StVec2 origin, f64 degrees, StColor tint);

// It inits lighting :)
void st_init_lighting();

// It frees lighting :)
void st_free_lighting();

/// Returns the current camera
StCamera st_camera(void);

/// Sets the current camera
void st_set_camera(StCamera cam);

/// As the name implies, it draws a 3D object
void st_draw_object_3d(StObject3D obj);

/// Does exactly what the name says
void st_draw_all_3d_objects(void);