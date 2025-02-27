#ifndef ST_VEC3_H
#define ST_VEC3_H
#include "core/core.hpp"

namespace starry {

/// world's bestest Vector3
struct Vec3 {
    float64 x = 0;
    float64 y = 0;
    float64 z = 0;

    Vec3(float64 x, float64 y, float64 z);
    Vec3 operator +(Vec3 b);
    Vec3 operator -(Vec3 b);
    Vec3 operator *(Vec3 b);
    Vec3 operator *(float64 b);
    Vec3 operator /(Vec3 b);
    Vec3 operator /(float64 b);
    Vec3 operator %(Vec3 b);
    Vec3 operator %(float64 b);
    bool operator <(Vec3 b);
    bool operator >(Vec3 b);
    bool operator <=(Vec3 b);
    bool operator >=(Vec3 b);
    bool operator ==(Vec3 b);
    bool operator !=(Vec3 b);
};

}

#endif // ST_VEC3_H
