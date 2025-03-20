#include <raylib.h>
#include "graphics.h"

void st_clear(StColor color)
{
	BeginDrawing();
	ClearBackground((Color){ .r = color.r, .g = color.g, .b = color.b, .a = color.a });
}

void st_end_drawing(void)
{
	EndDrawing();
}

void st_draw_texture(StTexture* texture, StVec2 pos, f64 degrees)
{
	st_draw_texture_ext(
		texture,
		(StVec2){0, 0},
		(StVec2){texture->width, texture->height},
		pos,
		(StVec2){texture->width, texture->height},
		(StVec2){0.5, 0.5},
		degrees,
		ST_WHITE
	);
}

void st_draw_texture_ext(StTexture* texture, StVec2 src_pos, StVec2 src_size, StVec2 dst_pos,
	StVec2 dst_size, StVec2 origin, f64 degrees, StColor tint)
{
	// akson dendryt
	DrawTexturePro(
		(Texture2D){
			.id = texture->id,
			.width = texture->width,
			.height = texture->height,
			.format = texture->format,
			.mipmaps = texture->mipmaps,
		},
		(Rectangle){ .x = src_pos.x, .y = src_pos.y, .width = src_size.x, .height = src_size.y },
		(Rectangle){ .x = dst_pos.x, .y = dst_pos.y, .width = dst_size.x, .height = dst_size.y },
		(Vector2){ .x = origin.x * dst_size.x, .y = origin.y * dst_size.y },
		degrees,
		(Color){ .r = tint.r, .g = tint.g, .b = tint.b, .a = tint.a }
	);
}