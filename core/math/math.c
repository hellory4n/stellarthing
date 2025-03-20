#include <stdlib.h>
#include "math.h"

i64 st_rand_int(i64 min, i64 max)
{
	return rand() % (max - min) + min;
}

u64 st_rand_uint(u64 min, u64 max)
{
	return rand() % (max - min) + min;
}

f64 st_rand_float(f64 min, f64 max)
{
	f64 scale = rand() / (f64)RAND_MAX; /* [0, 1.0] */
	return min + scale * ( max - min );
}

char st_rand_char(char min, char max)
{
	return rand() % (max - min) + min;
}

f64 st_deg2rad(f64 deg)
{
	return deg * (PI / 180.0);
}

f64 st_rad2deg(f64 rad)
{
	return rad * (180 / PI);
}

const char base64_chars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_";

void st_rand_base64(nint len, char* out)
{
	for (nint i = 0; i < len; i++) {
		u64 man = st_rand_uint(0, 63);
		out[i] = base64_chars[man];
	}
	out[len] = '\0';
}

f64 st_clamp(f64 val, f64 min, f64 max)
{
	if (val < min) return min;
	else if (val > max) return max;
	else return val;
}