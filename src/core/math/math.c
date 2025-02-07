#include "math.h"

int64 st_rand_int(int64 min, int64 max)
{
    return rand() % (max - min) + min;
}

uint64 st_rand_uint(uint64 min, uint64 max)
{
    return rand() % (max - min) + min;
}

float64 st_rand_float(float64 min, float64 max)
{
    float64 scale = rand() / (float64)RAND_MAX; /* [0, 1.0] */
    return min + scale * ( max - min );
}

char st_rand_char(char min, char max)
{
    return rand() % (max - min) + min;
}

float64 st_deg2rad(float64 deg)
{
    return deg * (ST_PI / 180);
}

float64 st_rad2deg(float64 rad)
{
    return rad * (180 / ST_PI);
}

void st_rand_base64(uint8 len, char* out)
{
    for (nint i = 0; i < len; i++) {
        uint64 type = st_rand_uint(0, 5);
        switch (type) {
            case 0: out[i] = st_rand_char('a', 'z' + 1); break;
            case 1: out[i] = st_rand_char('A', 'Z' + 1); break;
            case 2: out[i] = st_rand_char('0', '9' + 1); break;
            case 3: out[i] = '-'; break;
            case 4: out[i] = '_'; break;
        }
    }
    out[len] = '\0';
}