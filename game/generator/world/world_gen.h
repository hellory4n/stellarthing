#pragma once
#include "core/core.h"
#include "core/math/color.h"

#define ST_GEN_BASE_HEIGHT 0

/// Returns the block height at a certain position
f64 st_gen_get_block_height(i64 seed, i64 x, i64 z);

/// range is -0.5 to 0.5 i think??
StColor st_gen_get_color(f64 height);