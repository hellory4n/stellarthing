#pragma once
#include "core/core.h"

#ifndef PI
#define PI 3.141592653589793238463
#endif

/// Returns a random integer equal or greater than the min parameter and less than the max parameter
i64 st_rand_int(i64 min, i64 max);

/// Returns a random unsigned integer equal or greater than the min parameter and less than the max parameter
u64 st_rand_uint(u64 min, u64 max);

/// Returns a random float equal or greater than the min parameter and less than the max parameter
f64 st_rand_float(f64 min, f64 max);

/// Returns a random character equal or greater than the min parameter and less than the max parameter
char st_rand_char(char min, char max);

/// Converts degrees to radians
f64 st_deg2rad(f64 deg);

/// Converts radians to degrees
f64 st_rad2deg(f64 rad);

/// Returns a random base64 string (-_ instead of +/) with the specified length. please note your output
/// needs to be 1 character more than the string so it fits the ending null character
void st_rand_base64(nint len, char* out);

/// clamp
f64 st_clamp(f64 val, f64 min, f64 max);

/// lerp
f64 st_lerp(f64 a, f64 b, f64 t);

/// Similar to lerp, but inverse.
f64 st_inverse_lerp(f64 a, f64 b, f64 v);

/// Converts a number from one scale to another
f64 st_remap(f64 v, f64 src_min, f64 src_max, f64 dst_min, f64 dst_max);