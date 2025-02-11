#pragma once
#include "core/core.h"

/// vector3 but with integers
typedef struct {
    /// x
    int64 x;
    /// y
    int64 y;
    /// z
    int64 z;
} stvec3i;

/// adds 2 vector3s together
stvec3i stvec3i_add(stvec3i a, stvec3i b);

/// subtracts 2 vector3s together
stvec3i stvec3i_sub(stvec3i a, stvec3i b);

/// multiply 2 vector3s together
stvec3i stvec3i_mul(stvec3i a, stvec3i b);

/// divides 2 vector3s together
stvec3i stvec3i_div(stvec3i a, stvec3i b);

/// returns the remainder of diving 2 vector3s together
stvec3i stvec3i_mod(stvec3i a, stvec3i b);

/// returns true if the 2 vectors are equal. please note this may be fucky due to float precision and stuff
bool stvec3i_eq(stvec3i a, stvec3i b);

/// returns true if the 2 vectors aren't equal. please note this may be fucky due to float precision and stuff
bool stvec3i_neq(stvec3i a, stvec3i b);

/// returns true if vector a is greater than vector b.
bool stvec3i_gt(stvec3i a, stvec3i b);

/// returns true if vector a is greater than or equal to vector b.
bool stvec3i_gte(stvec3i a, stvec3i b);

/// returns true if vector a is less than vector b.
bool stvec3i_lt(stvec3i a, stvec3i b);

/// returns true if vector a is less than or equal to vector b.
bool stvec3i_lte(stvec3i a, stvec3i b);

/// negates the vector.
stvec3i stvec3i_neg(stvec3i a);

/// zero.
#define STVEC3I_ZERO (stvec3i){ 0, 0, 0 }