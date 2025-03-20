#include "color.h"

StColor st_rgba(u8 r, u8 g, u8 b, u8 a)
{
	return (StColor){
		.r = r,
		.g = g,
		.b = b,
		.a = a,
	};
}

StColor st_rgb(u8 r, u8 g, u8 b)
{
	return (StColor){
        .r = r,
        .g = g,
        .b = b,
        .a = 255,
    };
}