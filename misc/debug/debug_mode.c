#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "core/core.h"
#include "core/math/color.h"
#include "platform/input.h"
#include "platform/input_enums.h"
#include "misc/ui/ui.h"
#include "platform/window.h"
#include "debug_mode.h"

bool enabled = false;

void st_update_debug_mode(void)
{
	if (st_is_key_just_pressed(ST_KEY_F3)) {
		enabled = !enabled;
	}

	if (!enabled) {
		return;
	}

	// TODO there's more than 2 platforms
	#ifdef ST_LINUXBSD
	bool linux = true;
	#else
	bool linux = false;
	#endif

	#ifdef _DEBUG
	const char* build = "(debug build)";
	#else
	const char* build = "(release build)";
	#endif

	// :(
	char text[512];
	snprintf(text, 512, "Stellarthing %s, starry %s %s\nRunning on %s\nDisplay: %lix%li\n%li FPS", ST_GAME_VERSION, ST_STARRY_VERSION, build, linux ? "Linux/*BSD" : "Windows", st_window_get_size().x, st_window_get_size().y, st_window_get_fps());

	st_ui_window(0, 0, 400, ST_UI_RENDER_HEIGHT);
	st_ui_text(18, 18, text, ST_BLACK);
	st_ui_text(16, 16, text, ST_WHITE);
}