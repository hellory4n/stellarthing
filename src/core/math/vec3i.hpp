#ifndef ST_VEC3I_H
#define ST_VEC3I_H
#include "core/core.hpp"
#include "vec3.hpp"

namespace starry {

/// Vector3 but integer
struct Vec3i {
    int64 x;
    int64 y;
    int64 z;

    Vec3i(int64 x, int64 y, int64 z);
    Vec3i operator +(Vec3i b);
    Vec3i operator -(Vec3i b);
    Vec3i operator *(Vec3i b);
    Vec3i operator *(int64 b);
    Vec3i operator /(Vec3i b);
    Vec3i operator /(int64 b);
    Vec3i operator %(Vec3i b);
    Vec3i operator %(int64 b);
    bool operator <(Vec3i b);
    bool operator >(Vec3i b);
    bool operator <=(Vec3i b);
    bool operator >=(Vec3i b);
    bool operator ==(Vec3i b);
    bool operator !=(Vec3i b);
    explicit operator Vec3();
};

}

#endif // ST_VEC3I_H