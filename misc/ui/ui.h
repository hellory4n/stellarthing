#pragma once

#include "core/math/color.h"
#ifndef ST_UI_FONT_SIZE
#define ST_UI_FONT_SIZE 16
#endif

#ifndef ST_UI_SEPARATION
#define ST_UI_SEPARATION 8
#endif

#ifndef ST_UI_WIDGET_HEIGHT
#define ST_UI_WIDGET_HEIGHT 40
#endif

#ifndef ST_UI_RENDER_WIDTH
#define ST_UI_RENDER_WIDTH 1280
#endif

#ifndef ST_UI_RENDER_HEIGHT
#define ST_UI_RENDER_HEIGHT 720
#endif

/// As the name implies, it initializes UI.
void st_init_ui(void);

/// As the name implies, it frees UI.
void st_free_ui(void);

/// Help
void st_early_update_ui(void);

/// pleH
void st_late_update_ui(void);

// themes
// Draws regular text
void st_ui_text(const char* text, StColor color);

// Draws bold text
void st_ui_bold_text(const char* text, StColor color);

// Draws primary button, not an actual button, it's just drawing
void st_ui_draw_primary_button(f64 x, f64 y, f64 w, f64 h);

// Draws secondary button, not an actual button, it's just drawing
void st_ui_draw_secondary_button(f64 x, f64 y, f64 w, f64 h);

// Draws danger button, not an actual button, it's just drawing
void st_ui_draw_danger_button(f64 x, f64 y, f64 w, f64 h);

// Draws danger button, not an actual button, it's just drawing
void st_ui_draw_danger_button(f64 x, f64 y, f64 w, f64 h);