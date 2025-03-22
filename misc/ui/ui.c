#include <stddef.h>
#include <raylib.h>
#include "ui.h"

Font fontma;

void st_init_ui(void)
{
	// fontma = LoadFontEx("assets/Figtree-Regular", 16, NULL, 0);
	// ctx = InitNuklearEx(fontma, 16);
}

void st_free_ui(void)
{
	// UnloadNuklear(ctx);
	// UnloadFont(fontma);
}

void st_early_update_ui(void)
{
	// UpdateNuklear(ctx);
}

void st_late_update_ui(void)
{
	// DrawNuklear(ctx);
}
