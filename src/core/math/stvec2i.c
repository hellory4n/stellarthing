#include "stvec2i.h"

stvec2i stvec2i_add(stvec2i a, stvec2i b)
{
    return (stvec2i){ .x = a.x + b.x, .y = a.y + b.y };
}

stvec2i stvec2i_sub(stvec2i a, stvec2i b)
{
    return (stvec2i){ .x = a.x - b.x, .y = a.y - b.y };
}

stvec2i stvec2i_mul(stvec2i a, stvec2i b)
{
    return (stvec2i){ .x = a.x * b.x, .y = a.y * b.y };
}

stvec2i stvec2i_div(stvec2i a, stvec2i b)
{
    return (stvec2i){ .x = a.x / b.x, .y = a.y / b.y };
}

stvec2i stvec2i_mod(stvec2i a, stvec2i b)
{
    return (stvec2i){ .x = a.x % b.x, .y = a.y % b.y };
}

bool stvec2i_eq(stvec2i a, stvec2i b)
{
    return a.x == b.x && a.y == b.y;
}

bool stvec2i_neq(stvec2i a, stvec2i b)
{
    return a.x != b.x && a.y != b.y;
}

bool stvec2i_gt(stvec2i a, stvec2i b)
{
    return a.x > b.x && a.y > b.y;
}

bool stvec2i_gte(stvec2i a, stvec2i b)
{
    return a.x >= b.x && a.y >= b.y;
}

bool stvec2i_lt(stvec2i a, stvec2i b)
{
    return a.x < b.x && a.y < b.y;
}

bool stvec2i_lte(stvec2i a, stvec2i b)
{
    return a.x <= b.x && a.y <= b.y;
}

stvec2i stvec2i_neg(stvec2i a)
{
    return (stvec2i){ .x = -a.x, .y = -a.y };
}