#include "stvec3i.h"

stvec3i stvec3i_new(int64 x, int64 y, int64 z)
{
    return (stvec3i){ .x = x, .y = y, .z = z };
}

stvec3i stvec3i_add(stvec3i a, stvec3i b)
{
    return (stvec3i){ .x = a.x + b.x, .y = a.y + b.y, .z = a.z + b.z };
}

stvec3i stvec3i_sub(stvec3i a, stvec3i b)
{
    return (stvec3i){ .x = a.x - b.x, .y = a.y - b.y, .z = a.z - b.z };
}

stvec3i stvec3i_mul(stvec3i a, stvec3i b)
{
    return (stvec3i){ .x = a.x * b.x, .y = a.y * b.y, .z = a.z * b.z };
}

stvec3i stvec3i_div(stvec3i a, stvec3i b)
{
    return (stvec3i){ .x = a.x / b.x, .y = a.y / b.y, .z = a.z / b.z };
}

stvec3i stvec3i_mod(stvec3i a, stvec3i b)
{
    return (stvec3i){ .x = a.x % b.x, .y = a.y % b.y, .z = a.z % b.z };
}

bool stvec3i_eq(stvec3i a, stvec3i b)
{
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

bool stvec3i_neq(stvec3i a, stvec3i b)
{
    return a.x != b.x && a.y != b.y && a.z != b.z;
}

bool stvec3i_gt(stvec3i a, stvec3i b)
{
    return a.x > b.x && a.y > b.y && a.z > b.z;
}

bool stvec3i_gte(stvec3i a, stvec3i b)
{
    return a.x >= b.x && a.y >= b.y && a.z >= b.z;
}

bool stvec3i_lt(stvec3i a, stvec3i b)
{
    return a.x < b.x && a.y < b.y && a.z < b.z;
}

bool stvec3i_lte(stvec3i a, stvec3i b)
{
    return a.x <= b.x && a.y <= b.y && a.z <= b.z;
}

stvec3i stvec3i_neg(stvec3i a)
{
    return (stvec3i){ .x = -a.x, .y = -a.y, .z = -a.z };
}