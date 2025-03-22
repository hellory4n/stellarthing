#include <stddef.h>
#include <raylib.h>
#include "ui.h"

typedef struct {
	
} StButtonInstruction;

Font regular_font;
Font bold_font;

void st_init_ui(void)
{
	regular_font = LoadFontEx("assets/Figtree-Regular.ttf", ST_UI_FONT_SIZE, NULL, 0);
	bold_font = LoadFontEx("assets/Figtree-Regular.ttf", ST_UI_FONT_SIZE, NULL, 0);
}

void st_free_ui(void)
{
	UnloadFont(regular_font);
	UnloadFont(bold_font);
}

void st_early_update_ui(void)
{
	// UpdateNuklear(ctx);
}

void st_late_update_ui(void)
{
	// DrawNuklear(ctx);
}
