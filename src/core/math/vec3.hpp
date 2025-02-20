#ifndef ST_VEC3_H
#define ST_VEC3_H
#include "core/core.hpp"

namespace starry {

/// world's bestest vector3
struct vec3 {
    float64 x;
    float64 y;
    float64 z;

    vec3(float64 x, float64 y, float64 z);
    vec3 operator +(vec3 b);
    vec3 operator -(vec3 b);
    vec3 operator *(vec3 b);
    vec3 operator *(float64 b);
    vec3 operator /(vec3 b);
    vec3 operator /(float64 b);
    vec3 operator %(vec3 b);
    vec3 operator %(float64 b);
    bool operator <(vec3 b);
    bool operator >(vec3 b);
    bool operator <=(vec3 b);
    bool operator >=(vec3 b);
    bool operator ==(vec3 b);
    bool operator !=(vec3 b);
};

}

#endif // ST_VEC3_H
