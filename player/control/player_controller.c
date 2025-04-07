#include <raylib.h>
#include <rlFPCamera.h>
#include "player_controller.h"
#include "core/graphics.h"
#include "libtrippin.h"

static rlFPCamera cam;
static Model model;
static bool paused;
static bool ignore_input;

void player_controller_new(void)
{
	model = LoadModel("assets/model/bob_i_tried.vox");

	// init camera
	rlFPCameraInit(&cam, 90, (Vector3) { 0, 0, 0 });
	cam.MoveSpeed.z = 2;
	cam.MoveSpeed.x = 2;
	cam.FarPlane = 5000;
	// TODO custom flight/jumping/gravity whatever
	// fly up
	cam.ControlsKeys[4] = KEY_SPACE;
	// fly down
	cam.ControlsKeys[5] = KEY_LEFT_SHIFT;

	// rlfpcamera allows rotating camera with the arrow keys
	// we don't want that
	cam.ControlsKeys[6] = KEY_NULL;
	cam.ControlsKeys[7] = KEY_NULL;
	cam.ControlsKeys[8] = KEY_NULL;
	cam.ControlsKeys[9] = KEY_NULL;

	// sprint
	cam.ControlsKeys[10] = KEY_LEFT_CONTROL;

	tr_log(TR_LOG_INFO, "initialized player controller");
}

void player_controller_free(void)
{
	UnloadModel(model);

	tr_log(TR_LOG_INFO, "deinitialized player controller");
}

void player_controller_update(double _)
{
	if (IsKeyPressed(KEY_ESCAPE)) {
		paused = !paused;
	}

	if (!paused && !ignore_input) {
		rlFPCameraUpdate(&cam);

		Camera3D rlcam = cam.ViewCamera;
		graphics_set_camera(rlcam);
	}
	else {
		// rlfpcamera doesn't give the cursor back
		EnableCursor();

		// just ignore_input
		// player runs after UI crap so it would draw that after the crap
		// TODO make a decent pause menu
		if (paused) {
			TrColor sigma = tr_hex_rgba(0x00000077);
			DrawRectangle(0, 0, ST_2D_RENDER_WIDTH, ST_2D_RENDER_HEIGHT,
				*(Color*)(&sigma));
		}
	}

	if (!IsWindowFocused()) {
		EnableCursor();
	}

	// it's supposed to reset every frame :)
	ignore_input = false;
}

void player_controller_ignore_input(void)
{
	ignore_input = true;
}
