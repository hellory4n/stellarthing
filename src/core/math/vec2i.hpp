#ifndef ST_VEC2I_H
#define ST_VEC2I_H

#include "core/core.hpp"

namespace starry {

/// vector2 but with integers
struct vec2i {
    int64 x;
    int64 y;

    vec2i(int64 x, int64 y);
    vec2i operator +(vec2i b);
    vec2i operator -(vec2i b);
    vec2i operator *(vec2i b);
    vec2i operator *(int64 b);
    vec2i operator /(vec2i b);
    vec2i operator /(int64 b);
    vec2i operator %(vec2i b);
    vec2i operator %(int64 b);
    bool operator <(vec2i b);
    bool operator >(vec2i b);
    bool operator <=(vec2i b);
    bool operator >=(vec2i b);
    bool operator ==(vec2i b);
    bool operator !=(vec2i b);
};

}


#endif // ST_VEC2I_H
