#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <raylib.h>
#include "core/math/color.h"
#include "core/math/math.h"
#include "core/math/vec.h"
#include "core/math/rect.h"
#include "platform/input.h"
#include "platform/input_enums.h"
#include "ui.h"

// as the name implies, it's an ui id
typedef struct {
	nint owner;
	nint item;
	nint index;
} StUiId;

Font regular_font;
Font bold_font;

// it's a counter
i64 interacted_widgets;

RenderTexture2D ui_render;

StUiId hovered;
StUiId active;

static StVec2 virtual_mouse()
{
	f64 scale = fmin(
		GetRenderWidth() / (f64)ST_UI_RENDER_WIDTH,
		GetRenderHeight() / (f64)ST_UI_RENDER_HEIGHT
	);

	Vector2 mouse = GetMousePosition();
	StVec2 virt;
	virt.x = (mouse.x - (GetRenderWidth() - (ST_UI_RENDER_WIDTH * scale)) * 0.5) / scale;
	virt.y = (mouse.y - (GetRenderHeight() - (ST_UI_RENDER_HEIGHT * scale)) * 0.5) / scale;
	return virt;
}

void st_init_ui(void)
{
	regular_font = LoadFontEx("assets/Figtree/Figtree-Regular.ttf", 256, NULL, 0);
	bold_font = LoadFontEx("assets/Figtree/Figtree-Bold.ttf", 256, NULL, 0);
	SetTextLineSpacing(1);

	ui_render = LoadRenderTexture(ST_UI_RENDER_WIDTH, ST_UI_RENDER_HEIGHT);

	st_log("[UI] Loaded UI");
}

void st_free_ui(void)
{
	UnloadFont(regular_font);
	UnloadFont(bold_font);

	UnloadRenderTexture(ui_render);

	st_log("[UI] Freed UI");
}

void st_early_update_ui(void)
{
	interacted_widgets = 0;
	BeginTextureMode(ui_render);
}

void st_late_update_ui(void)
{
	EndTextureMode();

	f64 scale = fmin(
		GetRenderWidth() / (f64)ST_UI_RENDER_WIDTH,
		GetRenderHeight() / (f64)ST_UI_RENDER_HEIGHT
	);
	f64 x = (GetRenderWidth() - ST_UI_RENDER_WIDTH * scale) * 0.5;
	f64 y = (GetRenderHeight() - ST_UI_RENDER_HEIGHT * scale) * 0.5;
	f64 w = ST_UI_RENDER_WIDTH * scale;
	f64 h = ST_UI_RENDER_HEIGHT * scale;

	DrawTexturePro(
		ui_render.texture,
		(Rectangle){0, 0, ui_render.texture.width, -ui_render.texture.height},
		(Rectangle){x, y, w, h},
		(Vector2){0, 0}, 0, WHITE
	);
}

bool st_ui_is_interacting(void)
{
	return interacted_widgets >= 1;
}

void st_ui_text(f64 x, f64 y, const char* text, StColor color)
{
	DrawTextEx(
		regular_font,
		text,
		(Vector2){x, y},
		ST_UI_FONT_SIZE,
		1,
		(Color){color.r, color.g, color.b, color.a}
	);
}

void st_ui_bold_text(f64 x, f64 y, const char* text, StColor color)
{
	DrawTextEx(
		bold_font,
		text,
		(Vector2){x, y},
		ST_UI_FONT_SIZE,
		1,
		(Color){color.r, color.g, color.b, color.a}
	);
}

void st_ui_draw_primary_button(f64 x, f64 y, f64 w, f64 h)
{
	DrawRectangleRounded(
		(Rectangle){x, y, w, h},
		0.4, 4, (Color){0x7c, 0x4d, 0xff, 0xff}
	);
	DrawRectangleRoundedLinesEx(
		(Rectangle){x, y, w, h},
		0.4, 4, 2, (Color){0x7b, 0x1f, 0xa2, 0xff}
	);
}

void st_ui_draw_secondary_button(f64 x, f64 y, f64 w, f64 h)
{
	DrawRectangleRounded(
		(Rectangle){x, y, w, h},
		0.4, 4, (Color){0x26, 0x09, 0x2b, 0xff}
	);
	DrawRectangleRoundedLinesEx(
		(Rectangle){x, y, w, h},
		0.4, 4, 2, (Color){0x12, 0x04, 0x14, 0xff}
	);
}

void st_ui_draw_danger_button(f64 x, f64 y, f64 w, f64 h)
{
	DrawRectangleRounded(
		(Rectangle){x, y, w, h},
		0.4, 4, (Color){0xf4, 0x43, 0x36, 0xff}
	);
	DrawRectangleRoundedLinesEx(
		(Rectangle){x, y, w, h},
		0.4, 4, 2, (Color){0xd3, 0x2f, 0x2f, 0xff}
	);
}

void st_ui_draw_hover_outline(f64 x, f64 y, f64 w, f64 h)
{
	DrawRectangleRoundedLinesEx(
		(Rectangle){x, y, w, h},
		0.4, 4, 2, (Color){0xff, 0xff, 0xff, 0xff}
	);
}

void st_ui_draw_line_edit(f64 x, f64 y, f64 w, f64 h)
{
	DrawRectangleRounded(
		(Rectangle){x, y, w, h},
		0.4, 4, (Color){0x12, 0x04, 0x14, 0xff}
	);
	DrawRectangleRoundedLinesEx(
		(Rectangle){x, y, w, h},
		0.4, 4, 2, (Color){0xff, 0xff, 0xff, 0xff}
	);
}

void st_ui_draw_pressed_button(f64 x, f64 y, f64 w, f64 h)
{
	DrawRectangleRounded(
		(Rectangle){x, y, w, h},
		0.4, 4, (Color){0xff, 0xff, 0xff, 0x55}
	);
}

void st_ui_draw_slider(f64 x, f64 y, f64 w, f64 h, f64 grabber)
{
	// background
	DrawRectangleRounded(
		(Rectangle){x, y + (w / 4), w, h / 2},
		1, 12, (Color){0x26, 0x09, 0x2b, 0xff}
	);
	DrawRectangleRoundedLinesEx(
		(Rectangle){x, y + (w / 4), w, h / 2},
		1, 12, 2, (Color){0x12, 0x04, 0x14, 0xff}
	);

	// grabber
	// im sorry... im sorry... im sorry...
	DrawRectangleRounded(
		(Rectangle){
			st_clamp(x + (w * grabber) - h / 1.75, h / 2, w - h / 2),
			y, w, h
		},
		1, 12, (Color){0x7c, 0x4d, 0xff, 0xff}
	);
	DrawRectangleRoundedLinesEx(
		(Rectangle){
			st_clamp(x + (w * grabber) - h / 1.75, h / 2, w - h / 2),
			y, w, h
		},
		1, 12, 2, (Color){0x7b, 0x1f, 0xa2, 0xff}
	);
}

void st_ui_window(f64 x, f64 y, f64 w, f64 h)
{
	DrawRectangle(
		x, y, w, h,
		(Color){0x00, 0x00, 0x00, 0x77}
	);
	DrawRectangleLinesEx(
		(Rectangle){x, y, w, h}, 2,
		(Color){0xff, 0xff, 0xff, 0x45}
	);
}

bool st_ui_button(f64 x, f64 y, f64 w, f64 h, const char* text, StUiButtonStyle style)
{
	bool pressed = false;

	// center text:
	Vector2 text_size = MeasureTextEx(bold_font, text, ST_UI_FONT_SIZE, 1);
	StVec2 text_pos = (StVec2){
		(w / 2) - (text_size.x / 2),
		(h / 2) - (text_size.y / 2),
	};
	StColor text_color = ST_WHITE;

	switch (style) {
		case ST_UI_BUTTON_STYLE_PRIMARY: st_ui_draw_primary_button(x, y, w, h); break;
		case ST_UI_BUTTON_STYLE_SECONDARY: st_ui_draw_secondary_button(x, y, w, h); break;
		case ST_UI_BUTTON_STYLE_DANGER: st_ui_draw_danger_button(x, y, w, h); break;
	}

	// is it focused?
	StRect button_rect = {x, y, w, h};
	if (StRect_has_point(button_rect, virtual_mouse())) {
		st_ui_draw_hover_outline(x, y, w, h);

		// and is it pressed?
		if (st_is_mouse_button_just_released(ST_MOUSE_BUTTON_LEFT)) {
			pressed = true;
		}

		// different mouse thingy so it's not highlighted for 1 frame
		if (st_is_mouse_button_held(ST_MOUSE_BUTTON_LEFT)) {
			text_color = ST_BLACK;
			st_ui_draw_pressed_button(x, y, w, h);
		}
	}

	// finally draw text :)
	st_ui_bold_text(text_pos.x, text_pos.y, text, text_color);

	if (pressed) {
		interacted_widgets++;
	}

	return pressed;
}

void st_ui_toggle_button(f64 x, f64 y, f64 w, f64 h, const char* text, bool* out)
{
	// put "on" or "off" at the end
	char buf[256];
	if (*out) snprintf(buf, 256, "%s: on", text);
	else snprintf(buf, 256, "%s: off", text);

	// the actual button
	if (*out) {
		if (st_ui_button(x, y, w, h, buf, ST_UI_BUTTON_STYLE_PRIMARY)) {
			*out = false;
		}
	}
	else {
		if (st_ui_button(x, y, w, h, buf, ST_UI_BUTTON_STYLE_SECONDARY)) {
			*out = true;
		}
	}
}

void st_ui_cycle_button(f64 x, f64 y, f64 w, f64 h, const char* options[], nint option_len, nint* out)
{
	// TODO: i'm eventually gonna get a segfault from this :D
	if (st_ui_button(x, y, w, h, options[*out], ST_UI_BUTTON_STYLE_SECONDARY)) {
		*out = *out + 1;
		if (*out >= option_len) {
			*out = 0;
		}
	}
}

void st_ui_slider(f64 x, f64 y, f64 w, f64 h, f64 min, f64 max, f64* out)
{
	// TODO: dejankify this

	// some extra padding in the hitbox so it's less fucky
	StRect slider_rect = {x - 64, y, w + 64, y};
	if (StRect_has_point(slider_rect, virtual_mouse())) {
		if (st_is_mouse_button_held(ST_MOUSE_BUTTON_LEFT)) {
			interacted_widgets++;
			f64 t = (virtual_mouse().x - x) / w;
			*out = st_clamp(min + t * (max - min), min, max);
		}
	}
	st_ui_draw_slider(x, y, w, h, ((*out - min) / max) * 2);
}

void st_ui_line_edit(f64 x, f64 y, f64 w, f64 h, nint max_len, const char* placeholder, char** out)
{
	// TODO serious dejankifying needs to happen here

	// vertical centering
	Vector2 text_size;
	if (strlen(*out) == 0) {
		text_size = MeasureTextEx(bold_font, placeholder, ST_UI_FONT_SIZE, 1);
	}
	else {
		text_size = MeasureTextEx(bold_font, *out, ST_UI_FONT_SIZE, 1);
	}
	f64 text_y = (w / 2) - (text_size.y / 2);

	st_ui_draw_line_edit(x, y, w, h);

	// mate
	StRect rect = {x, y, w, h};
	if (StRect_has_point(rect, virtual_mouse())) {
		st_ui_draw_hover_outline(x, y, w, h);
		interacted_widgets++;

		// the character thingy is a queue
		// i assume that's because of unicode or the clipboard
		// idk
		i32 key = GetCharPressed();
		while (key > 0) {
			// you can't write control characters
			// TODO: unicode has more control characters than that
			if (key >= 32) {
				// TODO THIS WILL BREAK, WILL SEGFAULT, AND WILL DIE
				snprintf(*out, max_len, "%s%c", *out, (char)key);
			}

			// next character
			key = GetCharPressed();
		}

		// we all mank mistakes
		// this UI system is an example of a mistake
		nint len = strlen(*out);
		if (st_is_key_just_pressed(ST_KEY_BACKSPACE) && len > 0) {
			// we do this fuckery so you dont remove half a character
			// TODO THIS WILL SEGFAULT
			// TODO this will remove half a character sometimes
			(*out)[len - 1] = '\0';
		}
	}

	// huh
	BeginScissorMode(x, y, w, h);
	if (strlen(*out) == 0) {
		st_ui_text(x + 8, y + text_y, placeholder, st_rgba(255, 255, 255, 127));
	}
	else {
		st_ui_text(x + 8, y + text_y, *out, st_rgba(255, 255, 255, 127));
	}
	EndScissorMode();
}
