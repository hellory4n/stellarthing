#pragma once
#include "core/core.h"

/// vector2 but with integers
typedef struct {
    /// x
    int64 x;
    /// y
    int64 y;
} stvec2i;

/// makes a new vector
stvec2i stvec2i_new(int64 x, int64 y);

/// adds 2 vector2s together
stvec2i stvec2i_add(stvec2i a, stvec2i b);

/// subtracts 2 vector2s together
stvec2i stvec2i_sub(stvec2i a, stvec2i b);

/// multiply 2 vector2s together
stvec2i stvec2i_mul(stvec2i a, stvec2i b);

/// divides 2 vector2s together
stvec2i stvec2i_div(stvec2i a, stvec2i b);

/// returns the remainder of diving 2 vector2s together
stvec2i stvec2i_mod(stvec2i a, stvec2i b);

/// returns true if the 2 vectors are equal. please note this may be fucky due to float precision and stuff
bool stvec2i_eq(stvec2i a, stvec2i b);

/// returns true if the 2 vectors aren't equal. please note this may be fucky due to float precision and stuff
bool stvec2i_neq(stvec2i a, stvec2i b);

/// returns true if vector a is greater than vector b.
bool stvec2i_gt(stvec2i a, stvec2i b);

/// returns true if vector a is greater than or equal to vector b.
bool stvec2i_gte(stvec2i a, stvec2i b);

/// returns true if vector a is less than vector b.
bool stvec2i_lt(stvec2i a, stvec2i b);

/// returns true if vector a is less than or equal to vector b.
bool stvec2i_lte(stvec2i a, stvec2i b);

/// negates the vector.
stvec2i stvec2i_neg(stvec2i a);