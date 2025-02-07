#include <math.h>
#include "stvec3.h"

stvec3 stvec3_add(stvec3 a, stvec3 b)
{
    return (stvec3){ .x = a.x + b.x, .y = a.y + b.y, .z = a.z + b.z };
}

stvec3 stvec3_sub(stvec3 a, stvec3 b)
{
    return (stvec3){ .x = a.x - b.x, .y = a.y - b.y, .z = a.z - b.z };
}

stvec3 stvec3_mul(stvec3 a, stvec3 b)
{
    return (stvec3){ .x = a.x * b.x, .y = a.y * b.y, .z = a.z * b.z };
}

stvec3 stvec3_div(stvec3 a, stvec3 b)
{
    return (stvec3){ .x = a.x / b.x, .y = a.y / b.y, .z = a.z / b.z };
}

stvec3 stvec3_mod(stvec3 a, stvec3 b)
{
    return (stvec3){ .x = fmod(a.x, b.x), .y = fmod(a.y, b.y), .z = fmod(a.z, b.z) };
}

bool stvec3_eq(stvec3 a, stvec3 b)
{
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

bool stvec3_neq(stvec3 a, stvec3 b)
{
    return a.x != b.x && a.y != b.y && a.z != b.z;
}

bool stvec3_gt(stvec3 a, stvec3 b)
{
    return a.x > b.x && a.y > b.y && a.z > b.z;
}

bool stvec3_gte(stvec3 a, stvec3 b)
{
    return a.x >= b.x && a.y >= b.y && a.z >= b.z;
}

bool stvec3_lt(stvec3 a, stvec3 b)
{
    return a.x < b.x && a.y < b.y && a.z < b.z;
}

bool stvec3_lte(stvec3 a, stvec3 b)
{
    return a.x <= b.x && a.y <= b.y && a.z <= b.z;
}

stvec3 stvec3_neg(stvec3 a)
{
    return (stvec3){ .x = -a.x, .y = -a.y, .z = -a.z };
}