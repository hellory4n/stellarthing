#include <stddef.h>
#include <raylib.h>
#include "core/math/math.h"
#include "ui.h"

Font regular_font;
Font bold_font;
i64 interacted_widgets;

void st_init_ui(void)
{
	regular_font = LoadFontEx("assets/Figtree-Regular.ttf", ST_UI_FONT_SIZE, NULL, 0);
	bold_font = LoadFontEx("assets/Figtree-Bold.ttf", ST_UI_FONT_SIZE, NULL, 0);
	SetTextLineSpacing(1);
}

void st_free_ui(void)
{
	UnloadFont(regular_font);
	UnloadFont(bold_font);
}

void st_update_ui(void)
{
	interacted_widgets = 0;
}

bool st_ui_is_interacting(void)
{
	return interacted_widgets >= 1;
}

void st_ui_draw_text(f64 x, f64 y, const char* text, StColor color)
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

void st_ui_draw_bold_text(f64 x, f64 y, const char* text, StColor color)
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
	DrawRectangleRounded(
		(Rectangle){x, y + (w / 4), w, h / 2},
		1, 12, (Color){0x12, 0x04, 0x14, 0xff}
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

void st_ui_draw_window(f64 x, f64 y, f64 w, f64 h)
{
	DrawRectangle(x, y, w, h, (Color){0x00, 0x00, 0x00, 0x77});
	DrawRectangleLinesEx(
		(Rectangle){x, y, w, h}, 1, (Color){0xff, 0xff, 0xff, 0x45}
	);
}