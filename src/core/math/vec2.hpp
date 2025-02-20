#ifndef ST_VEC2_H
#define ST_VEC2_H
#include "core/core.hpp"

namespace starry {

/// world's bestest vector2
struct vec2 {
    float64 x;
    float64 y;

    vec2(float64 x, float64 y);
    vec2 operator +(vec2 b);
    vec2 operator -(vec2 b);
    vec2 operator *(vec2 b);
    vec2 operator *(float64 b);
    vec2 operator /(vec2 b);
    vec2 operator /(float64 b);
    vec2 operator %(vec2 b);
    vec2 operator %(float64 b);
    bool operator <(vec2 b);
    bool operator >(vec2 b);
    bool operator <=(vec2 b);
    bool operator >=(vec2 b);
    bool operator ==(vec2 b);
    bool operator !=(vec2 b);
};

}

#endif // ST_VEC2_H
