#include <rlFPCamera.h>
#include <stdio.h>
#include "core/core.h"
#include "core/math/color.h"
#include "core/math/vec.h"
#include "misc/ui/ui.h"
#include "platform/graphics/graphics.h"
#include "platform/graphics/model.h"
#include "platform/input.h"
#include "platform/input_enums.h"
#include "raylib.h"
#include "player.h"

StModel* bob;
rlFPCamera cam;
bool paused = false;
f64 fov = 90;

void st_init_player(void)
{
	bob = StModel_new("assets/species/bob.glb");

	// init camera
	rlFPCameraInit(&cam, 90, (Vector3) { 1, 0, 0 });
    cam.MoveSpeed.z = 1;
    cam.MoveSpeed.x = 1;
    cam.FarPlane = 5000;

	st_log("[PLAYER] Setup player");
}

void st_free_player(void)
{
	st_log("[PLAYER] Freed player");
}

void st_update_player(void)
{
	// f64 dt = st_window_get_delta_time();

	if (st_is_key_just_pressed(ST_KEY_ESCAPE)) {
		paused = !paused;
	}

	if (!paused) {
		rlFPCameraUpdate(&cam);

		// convert to stcamera
		Camera3D rlcam = cam.ViewCamera;
		st_set_camera((StCamera){
			.position = (StVec3){rlcam.position.x, rlcam.position.y, rlcam.position.z},
			.fov = rlcam.fovy,
			.perspective = true,
			.target = (StVec3){rlcam.target.x, rlcam.target.y, rlcam.target.z},
		});
	}
	else {
		// rlfpcamera doesn't give the cursor back
		EnableCursor();

		// pause screen
		st_ui_window(0, 0, ST_UI_RENDER_WIDTH, ST_UI_RENDER_HEIGHT);

		st_ui_bold_text(8, 8, "Paused", ST_WHITE);
		st_ui_slider(8, 24+8, 300, 40, 45, 180, &fov);
		cam.FOV.y = fov;

		char version[64];
		snprintf(version, sizeof(version), "Stellarthing %s", ST_GAME_VERSION);
		st_ui_text(8, 700-16, version, ST_WHITE);
	}
}