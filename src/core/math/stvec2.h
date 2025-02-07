#pragma once
#include "core/core.h"

/// the world's worst vector2
typedef struct {
    /// x
    float64 x;
    /// y
    float64 y;
} stvec2;

/// adds 2 vector2s together
stvec2 stvec2_add(stvec2 a, stvec2 b);

/// subtracts 2 vector2s together
stvec2 stvec2_sub(stvec2 a, stvec2 b);

/// multiply 2 vector2s together
stvec2 stvec2_mul(stvec2 a, stvec2 b);

/// divides 2 vector2s together
stvec2 stvec2_div(stvec2 a, stvec2 b);

/// returns the remainder of diving 2 vector2s together
stvec2 stvec2_mod(stvec2 a, stvec2 b);

/// returns true if the 2 vectors are equal. please note this may be fucky due to float precision and stuff
bool stvec2_eq(stvec2 a, stvec2 b);

/// returns true if the 2 vectors aren't equal. please note this may be fucky due to float precision and stuff
bool stvec2_neq(stvec2 a, stvec2 b);

/// returns true if vector a is greater than vector b.
bool stvec2_gt(stvec2 a, stvec2 b);

/// returns true if vector a is greater than or equal to vector b.
bool stvec2_gte(stvec2 a, stvec2 b);

/// returns true if vector a is less than vector b.
bool stvec2_lt(stvec2 a, stvec2 b);

/// returns true if vector a is less than or equal to vector b.
bool stvec2_lte(stvec2 a, stvec2 b);

/// negates the vector.
stvec2 stvec2_neg(stvec2 a);