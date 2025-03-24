#include <assert.h>
#include <stdbool.h>
#include "platform/input.h"
#include "platform/input_enums.h"
#include "misc/ui/ui.h"
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

	st_ui_text(0, 0, "please", ST_WHITE);

	/*struct nk_context* ctx = st_ui_ctx();
	bool visible = nk_begin(ctx, "debug mode", nk_rect(0, 0, 300, 300), 0);
	st_assert(!visible, "sir what the fuck");
	if (visible) {
		nk_layout_row_push(ctx, 100);
		nk_label(ctx, "Sigma sigma\non the wall", NK_TEXT_ALIGN_LEFT);
	}
	nk_end(ctx);*/
}