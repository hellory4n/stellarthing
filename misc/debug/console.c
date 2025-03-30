#include "core/core.h"
#include "misc/ui/ui.h"
#include "platform/input.h"
#include "console.h"

bool console_enabled = false;

void st_init_console(void) {}

void st_free_console(void) {}

void st_update_console(void)
{
	if (st_is_key_just_pressed(ST_KEY_F2)) {
		console_enabled = !console_enabled;
	}

	if (!console_enabled) return;

	st_ui_window(0, 0, ST_UI_RENDER_WIDTH, 40);
}