#pragma once
#include "core/core.h"

/// the world's worst vector3
typedef struct {
    /// x
    float64 x;
    /// y
    float64 y;
    /// z
    float64 z;
} stvec3;

/// adds 2 vector3s together
stvec3 stvec3_add(stvec3 a, stvec3 b);

/// subtracts 2 vector3s together
stvec3 stvec3_sub(stvec3 a, stvec3 b);

/// multiply 2 vector3s together
stvec3 stvec3_mul(stvec3 a, stvec3 b);

/// divides 2 vector3s together
stvec3 stvec3_div(stvec3 a, stvec3 b);

/// returns the remainder of diving 2 vector3s together
stvec3 stvec3_mod(stvec3 a, stvec3 b);

/// returns true if the 2 vectors are equal. please note this may be fucky due to float precision and stuff
bool stvec3_eq(stvec3 a, stvec3 b);

/// returns true if the 2 vectors aren't equal. please note this may be fucky due to float precision and stuff
bool stvec3_neq(stvec3 a, stvec3 b);

/// returns true if vector a is greater than vector b.
bool stvec3_gt(stvec3 a, stvec3 b);

/// returns true if vector a is greater than or equal to vector b.
bool stvec3_gte(stvec3 a, stvec3 b);

/// returns true if vector a is less than vector b.
bool stvec3_lt(stvec3 a, stvec3 b);

/// returns true if vector a is less than or equal to vector b.
bool stvec3_lte(stvec3 a, stvec3 b);

/// negates the vector.
stvec3 stvec3_neg(stvec3 a);