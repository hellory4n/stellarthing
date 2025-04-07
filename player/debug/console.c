#include <libtrippin.h>
#include "console.h"
#include "core/graphics.h"
#include "raylib.h"

static bool enabled;

void console_init(void)
{
	tr_log(TR_LOG_INFO, "initialized console");
}

void console_free(void)
{
	tr_log(TR_LOG_INFO, "deinitialized console");
}

void console_update(void)
{
	if (IsKeyPressed(KEY_F2)) {
		enabled = !enabled;
	}

	if (!enabled) return;

	DrawRectangle(0, 0, ST_2D_RENDER_WIDTH, 40, BLACK);
}
