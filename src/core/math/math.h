#pragma once
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "core/core.h"
#include "core/collections/stlist.h"

#ifndef PI
#define PI 3.141592653589793238463
#endif

/// returns a random integer equal or greater than the min parameter and less than the max parameter
int64 st_rand_int(int64 min, int64 max);

/// returns a random unsigned integer equal or greater than the min parameter and less than the max parameter
uint64 st_rand_uint(uint64 min, uint64 max);

/// returns a random float equal or greater than the min parameter and less than the max parameter
float64 st_rand_float(float64 min, float64 max);

/// returns a random character equal or greater than the min parameter and less than the max parameter
char st_rand_char(char min, char max);

/// converts degrees to radians
float64 st_deg2rad(float64 deg);

/// converts radians to degrees
float64 st_rad2deg(float64 rad);

/// returns a random base64 string (-_ instead of +/) with the specified length. please note your output needs to be 1 character more than the string so it fits the ending null character
void st_rand_base64(uint8 len, char* out);