#ifndef ST_VEC3I_H
#define ST_VEC3I_H
#include "core/core.hpp"

namespace starry {

/// vector3 but integer
struct vec3i {
    int64 x;
    int64 y;
    int64 z;

    vec3i(int64 x, int64 y, int64 z);
    vec3i operator +(vec3i b);
    vec3i operator -(vec3i b);
    vec3i operator *(vec3i b);
    vec3i operator *(int64 b);
    vec3i operator /(vec3i b);
    vec3i operator /(int64 b);
    vec3i operator %(vec3i b);
    vec3i operator %(int64 b);
    bool operator <(vec3i b);
    bool operator >(vec3i b);
    bool operator <=(vec3i b);
    bool operator >=(vec3i b);
    bool operator ==(vec3i b);
    bool operator !=(vec3i b);
};

}

#endif // ST_VEC3I_H