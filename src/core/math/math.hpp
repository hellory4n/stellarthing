#ifndef ST_MATH_H
#define ST_MATH_H
#include <stdlib.h>
#include <math.h>
#include "core/core.hpp"

namespace starry {

// pi
#define PI 3.141592653589793238463

/// returns a random integer equal or greater than the min parameter and less than the max parameter
int64 rand_int(int64 min, int64 max);

/// returns a random unsigned integer equal or greater than the min parameter and less than the max parameter
uint64 rand_uint(uint64 min, uint64 max);

/// returns a random float equal or greater than the min parameter and less than the max parameter
float64 rand_float(float64 min, float64 max);

/// returns a random character equal or greater than the min parameter and less than the max parameter
char rand_char(char min, char max);

/// converts degrees to radians
float64 deg2rad(float64 deg);

/// converts radians to degrees
float64 rad2deg(float64 rad);

/// returns a random base64 string (-_ instead of +/) with the specified length. please note your output needs to be 1 character more than the string so it fits the ending null character
void rand_base64(uint8 len, char* out);

/// clamp
float64 clamp(float64 val, float64 min, float64 max);

}

#endif // ST_MATH_H
