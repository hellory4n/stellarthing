#ifndef ST_VEC2_H
#define ST_VEC2_H
#include "core/core.hpp"

namespace starry {

/// world's bestest Vector2
struct Vec2 {
    float64 x;
    float64 y;

    Vec2(float64 x, float64 y);
    Vec2 operator +(Vec2 b);
    Vec2 operator -(Vec2 b);
    Vec2 operator *(Vec2 b);
    Vec2 operator *(float64 b);
    Vec2 operator /(Vec2 b);
    Vec2 operator /(float64 b);
    Vec2 operator %(Vec2 b);
    Vec2 operator %(float64 b);
    bool operator <(Vec2 b);
    bool operator >(Vec2 b);
    bool operator <=(Vec2 b);
    bool operator >=(Vec2 b);
    bool operator ==(Vec2 b);
    bool operator !=(Vec2 b);
};

}

#endif // ST_VEC2_H
