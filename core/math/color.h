#pragma once
#include "core/core.h"

/// The world's worst color type
typedef struct {
    /// Red, from 0 to 255
    u8 r;
    /// Green, from 0 to 255
    u8 g;
    /// Blue, from 0 to 255
    u8 b;
    /// Alpha (transparency), from 0 to 255
    u8 a;
} StColor;

/// white
#define ST_WHITE (StColor){ .r = 255, .g = 255, .b = 255, .a = 255 }

/// black
#define ST_BLACK (StColor){ .r = 0, .g = 0, .b = 0, .a = 255 }

/// transparent
#define ST_TRANSPARENT (StColor){ .r = 0, .g = 0, .b = 0, .a = 0 }

/// Makes a new color with transparency
StColor st_rgba(u8 r, u8 g, u8 b, u8 a);

/// Makes a new color with a default transparency of 255 (completely opaque)
StColor st_rgb(u8 r, u8 g, u8 b);