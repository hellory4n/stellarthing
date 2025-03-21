#pragma once
#include <nuklear.h>

/// As the name implies, it initializes UI.
void st_init_ui(void);

/// As the name implies, it frees UI.
void st_free_ui(void);

/// Help
void st_early_update_ui(void);

/// pleH
void st_late_update_ui(void);

/// Gets the nuklear context
struct nk_context* st_ui_ctx(void);