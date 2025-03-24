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

/// Button style.
typedef enum {
	ST_UI_BUTTON_STYLE_PRIMARY,
	ST_UI_BUTTON_STYLE_SECONDARY,
	ST_UI_BUTTON_STYLE_DANGER,
} StUiButtonStyle;

/// As the name implies, it initializes UI.
void st_init_ui(void);

/// As the name implies, it frees UI.
void st_free_ui(void);

/// Help
void st_update_ui(void);

/// If true, the user is interacting with UI :)
bool st_ui_is_interacting(void);

// Draws regular text
void st_ui_text(f64 x, f64 y, const char* text, StColor color);

/// Draws bold text
void st_ui_bold_text(f64 x, f64 y, const char* text, StColor color);

/// Draws primary button, not an actual button, it's just drawing
void st_ui_draw_primary_button(f64 x, f64 y, f64 w, f64 h);

/// Draws secondary button, not an actual button, it's just drawing
void st_ui_draw_secondary_button(f64 x, f64 y, f64 w, f64 h);

/// Draws danger button, not an actual button, it's just drawing
void st_ui_draw_danger_button(f64 x, f64 y, f64 w, f64 h);

/// Draws hover outline
void st_ui_draw_hover_outline(f64 x, f64 y, f64 w, f64 h);

/// Draws line edit, not an actual line edit, it's just drawing
void st_ui_draw_line_edit(f64 x, f64 y, f64 w, f64 h);

/// Draws pressed button, not an actual button, it's just drawing
void st_ui_draw_pressed_button(f64 x, f64 y, f64 w, f64 h);

/// Draws slider, not an actual slider, it's just drawing. Grabber is from 0 to 1
void st_ui_draw_slider(f64 x, f64 y, f64 w, f64 h, f64 grabber);

/// ha
void st_ui_window(f64 x, f64 y, f64 w, f64 h);

/// Makes a button, and returns true if it was pressed. Positioning and size are handled through
/// layouts.
bool st_ui_button(f64 x, f64 y, f64 w, f64 h, const char* text, StUiButtonStyle style);

/// A button that toggles. Writes the state into out.
void st_ui_toggle_button(f64 x, f64 y, f64 w, f64 h, const char* text, bool* out);

/// Button that cycles through options. How efficient. Writes the index of the current option into
/// out.
void st_ui_cycle_button(f64 x, f64 y, f64 w, f64 h, const char* options[], nint option_len, nint* out);

/// Slider. Writes value into out.
void st_ui_slider(f64 x, f64 y, f64 w, f64 h, f64 min, f64 max, f64* out);

/// Line edit. Writes whatever was written into out. Make sure it can fit whatever the max length is.
void st_ui_line_edit(f64 x, f64 y, f64 w, f64 h, nint max_len, const char* placeholder, char** out);
