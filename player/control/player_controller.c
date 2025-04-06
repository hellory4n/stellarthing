#include <raylib.h>
#include "player_controller.h"
#include "core/graphics.h"
#include "libtrippin.h"

Camera3D camera;
Model model;

void player_controller_new(void)
{
	model = LoadModel("assets/model/bob_i_tried.vox");
}

void player_controller_free(void)
{
	UnloadModel(model);
}

void player_controller_update(double _)
{
	graphics_set_camera((Camera3D){
		.position = (Vector3){0, 2, -5},
		.up = (Vector3){0, 1, 0},
		.fovy = 90,
		.target = (Vector3){1, 0.5, -1},
		.projection = CAMERA_PERSPECTIVE,
	});
	graphics_draw_3d_obj((Object3D){
		.model = model,
		.scale = (TrVec3f){1, 1, 1},
		.tint = TR_WHITE,
	});
}
