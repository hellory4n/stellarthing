#pragma once
#include "core/math/color.h"
#include "core/math/rect.h"

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

/// Where in the screen is the UI in
typedef enum {
	ST_UI_ANCHOR_TOP_LEFT,
	ST_UI_ANCHOR_TOP_CENTER,
	ST_UI_ANCHOR_TOP_RIGHT,
	ST_UI_ANCHOR_CENTER_LEFT,
	ST_UI_ANCHOR_CENTER,
	ST_UI_ANCHOR_CENTER_RIGHT,
	ST_UI_ANCHOR_BOTTOM_LEFT,
	ST_UI_ANCHOR_BOTTOM_CENTER,
	ST_UI_ANCHOR_BOTTOM_RIGHT,
} StUiAnchor;

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
void st_early_update_ui(void);

/// pleH
void st_late_update_ui(void);

// themes

// Draws regular text
void st_ui_draw_text(f64 x, f64 y, const char* text, StColor color);

/// Draws bold text
void st_ui_draw_bold_text(f64 x, f64 y, const char* text, StColor color);

/// Draws primary button, not an actual button, it's just drawing
void st_ui_draw_primary_button(f64 x, f64 y, f64 w, f64 h);

/// Draws secondary button, not an actual button, it's just drawing
void st_ui_draw_secondary_button(f64 x, f64 y, f64 w, f64 h);

/// Draws danger button, not an actual button, it's just drawing
void st_ui_draw_danger_button(f64 x, f64 y, f64 w, f64 h);

/// Draws danger button, not an actual button, it's just drawing
void st_ui_draw_danger_button(f64 x, f64 y, f64 w, f64 h);

/// Draws hover outline
void st_ui_draw_hover_outline(f64 x, f64 y, f64 w, f64 h);

/// Draws line edit, not an actual line edit, it's just drawing
void st_ui_draw_line_edit(f64 x, f64 y, f64 w, f64 h);

/// Draws pressed button, not an actual button, it's just drawing
void st_ui_draw_pressed_button(f64 x, f64 y, f64 w, f64 h);

/// Draws slider, not an actual slider, it's just drawing
void st_ui_draw_slider(f64 x, f64 y, f64 w, f64 h);

/// Draws window, not an actual window, it's just drawing
void st_ui_draw_window(f64 x, f64 y, f64 w, f64 h);

// layouts

/// Calculates the widget size based on whatever the current layout is
StRect st_ui_get_size(void);

/// Windows are great. They're not OS window, they're internal windows where you put everything else
void st_ui_window_start(StUiAnchor anchor, f64 width, f64 height);

/// Ends the window. It works like curly braces.
void st_ui_window_end(void);

/// Starts a vertical list
void st_ui_vlist_start(void);

/// Ends a vertical list
void st_ui_vlist_end(void);

/// Starts a horizontal list
void st_ui_hlist_start(void);

/// Ends a horizontal list
void st_ui_hlist_end(void);

/// widgets

// Draws regular text using the current layout
void st_ui_text(const char* text, StColor color);

/// Draws bold text
void st_ui_bold_text(const char* text, StColor color);

/// Makes a button, and returns true if it was pressed. Positioning and size are handled through
/// layouts.
bool st_ui_button(const char* text, StUiButtonStyle style);

/// A button that toggles. Writes the state into out.
void st_ui_toggle_button(const char* text, bool* out);

/// Button that cycles through options. How efficient. Writes the index of the current option into
/// out.
void st_ui_cycle_button(const char* options[], nint option_len, nint* out);

/// Slider. Writes value into out.
void st_ui_slider(f64 min, f64 max, f64* out);

/// Line edit. Writes whatever was written into out. Make sure it can fit whatever the max length is.
void st_ui_line_edit(nint max_len, const char* placeholder, const char** out);