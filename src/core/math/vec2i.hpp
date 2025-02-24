#ifndef ST_VEC2I_H
#define ST_VEC2I_H
#include "core/core.hpp"
#include "vec2.hpp"

namespace starry {

/// vector2 but with integers
struct Vec2i {
    int64 x;
    int64 y;

    Vec2i(int64 x, int64 y);
    Vec2i operator +(Vec2i b);
    Vec2i operator -(Vec2i b);
    Vec2i operator *(Vec2i b);
    Vec2i operator *(int64 b);
    Vec2i operator /(Vec2i b);
    Vec2i operator /(int64 b);
    Vec2i operator %(Vec2i b);
    Vec2i operator %(int64 b);
    bool operator <(Vec2i b);
    bool operator >(Vec2i b);
    bool operator <=(Vec2i b);
    bool operator >=(Vec2i b);
    bool operator ==(Vec2i b);
    bool operator !=(Vec2i b);
    explicit operator Vec2();
};

}

#endif // ST_VEC2I_H
