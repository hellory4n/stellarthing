#include <math.h>
#include "stvec2.h"

stvec2 stvec2_new(float64 x, float64 y)
{
    return (stvec2){ .x = x, .y = y };
}

stvec2 stvec2_add(stvec2 a, stvec2 b)
{
    return (stvec2){ .x = a.x + b.x, .y = a.y + b.y };
}

stvec2 stvec2_sub(stvec2 a, stvec2 b)
{
    return (stvec2){ .x = a.x - b.x, .y = a.y - b.y };
}

stvec2 stvec2_mul(stvec2 a, stvec2 b)
{
    return (stvec2){ .x = a.x * b.x, .y = a.y * b.y };
}

stvec2 stvec2_div(stvec2 a, stvec2 b)
{
    return (stvec2){ .x = a.x / b.x, .y = a.y / b.y };
}

stvec2 stvec2_mod(stvec2 a, stvec2 b)
{
    return (stvec2){ .x = fmod(a.x, b.x), .y = fmod(a.y, b.y) };
}

bool stvec2_eq(stvec2 a, stvec2 b)
{
    return a.x == b.x && a.y == b.y;
}

bool stvec2_neq(stvec2 a, stvec2 b)
{
    return a.x != b.x && a.y != b.y;
}

bool stvec2_gt(stvec2 a, stvec2 b)
{
    return a.x > b.x && a.y > b.y;
}

bool stvec2_gte(stvec2 a, stvec2 b)
{
    return a.x >= b.x && a.y >= b.y;
}

bool stvec2_lt(stvec2 a, stvec2 b)
{
    return a.x < b.x && a.y < b.y;
}

bool stvec2_lte(stvec2 a, stvec2 b)
{
    return a.x <= b.x && a.y <= b.y;
}

stvec2 stvec2_neg(stvec2 a)
{
    return (stvec2){ .x = -a.x, .y = -a.y };
}