#pragma once
#include "core.h"

/// the world's worst color type
typedef struct {
    uint8 r;
    uint8 g;
    uint8 b;
    uint8 a;
} stcolor;

/// white
#define ST_WHITE (stcolor){ .r = 255, .g = 255, .b = 255, .a = 255 };

/// black
#define ST_BLACK (stcolor){ .r = 0, .g = 0, .b = 0, .a = 255 };

/// transparent
#define ST_TRANSPARENT (stcolor){ .r = 0, .g = 0, .b = 0, .a = 0 };