#include "math.hpp"

namespace starry {

int64 rand_int(int64 min, int64 max)
{
    return rand() % (max - min) + min;
}

uint64 rand_uint(uint64 min, uint64 max)
{
    return rand() % (max - min) + min;
}

float64 rand_float(float64 min, float64 max)
{
    float64 scale = rand() / (float64)RAND_MAX; /* [0, 1.0] */
    return min + scale * ( max - min );
}

char rand_char(char min, char max)
{
    return rand() % (max - min) + min;
}

float64 deg2rad(float64 deg)
{
    return deg * (PI / 180.0);
}

float64 rad2deg(float64 rad)
{
    return rad * (180 / PI);
}

const char base64_chars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_";

void rand_base64(uint8 len, char* out)
{
    for (nint i = 0; i < len; i++) {
        uint64 man = rand_uint(0, 63);
        out[i] = base64_chars[man];
    }
    out[len] = '\0';
}

float64 clamp(float64 val, float64 min, float64 max)
{
    if (val < min) return min;
    else if (val > max) return max;
    else return val;
}

}