#pragma once
#include <math.h>
#include "core.h"

/// vector2 but with integers
typedef struct {
    int64 x;
    int64 y;
} stvec2i;

/// adds 2 vector2s together
stvec2i stvec2i_add(stvec2i a, stvec2i b)
{
    return (stvec2i){ .x = a.x + b.x, .y = a.y + b.y };
}

/// adds 2 vector2s together
stvec2i stvec2i_sub(stvec2i a, stvec2i b)
{
    return (stvec2i){ .x = a.x - b.x, .y = a.y - b.y };
}

/// adds 2 vector2s together
stvec2i stvec2i_mul(stvec2i a, stvec2i b)
{
    return (stvec2i){ .x = a.x * b.x, .y = a.y * b.y };
}

/// adds 2 vector2s together
stvec2i stvec2i_div(stvec2i a, stvec2i b)
{
    return (stvec2i){ .x = a.x / b.x, .y = a.y / b.y };
}

/// returns the remainder of diving 2 vector2s together
stvec2i stvec2i_mod(stvec2i a, stvec2i b)
{
    return (stvec2i){ .x = a.x % b.x, .y = a.y % b.y };
}

/// returns true if the 2 vectors are equal. please note this may be fucky due to float precision and stuff
bool stvec2i_eq(stvec2i a, stvec2i b)
{
    return a.x == b.x && a.y == b.y;
}

/// returns true if the 2 vectors aren't equal. please note this may be fucky due to float precision and stuff
bool stvec2i_neq(stvec2i a, stvec2i b)
{
    return a.x != b.x && a.y != b.y;
}

/// returns true if vector a is greater than vector b.
bool stvec2i_gt(stvec2i a, stvec2i b)
{
    return a.x > b.x && a.y > b.y;
}

/// returns true if vector a is greater than or equal to vector b.
bool stvec2i_gte(stvec2i a, stvec2i b)
{
    return a.x >= b.x && a.y >= b.y;
}

/// returns true if vector a is less than vector b.
bool stvec2i_lt(stvec2i a, stvec2i b)
{
    return a.x < b.x && a.y < b.y;
}

/// returns true if vector a is less than or equal to vector b.
bool stvec2i_lte(stvec2i a, stvec2i b)
{
    return a.x <= b.x && a.y <= b.y;
}

/// negates the vector.
stvec2i stvec2i_neg(stvec2i a)
{
    return (stvec2i){ .x = -a.x, .y = -a.y };
}