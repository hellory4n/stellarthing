#include <math.h>
#include "vec2i.hpp"

namespace starry {

vec2i::vec2i(int64 x, int64 y)
{
    this->x = x;
    this->y = y;
}

vec2i vec2i::operator +(vec2i b)
{
    return vec2i(this->x + b.x, this->y + b.y);
}

vec2i vec2i::operator -(vec2i b)
{
    return vec2i(this->x - b.x, this->y - b.y);
}

vec2i vec2i::operator *(vec2i b)
{
    return vec2i(this->x * b.x, this->y * b.y);
}

vec2i vec2i::operator *(int64 b)
{
    return vec2i(this->x * b, this->y * b);
}

vec2i vec2i::operator /(vec2i b)
{
    return vec2i(this->x / b.x, this->y / b.y);
}

vec2i vec2i::operator /(int64 b)
{
    return vec2i(this->x / b, this->y / b);
}

vec2i vec2i::operator %(vec2i b)
{
    return vec2i(fmod(this->x, b.x), fmod(this->y, b.y));
}

vec2i vec2i::operator %(int64 b)
{
    return vec2i(this->x % b, this->y % b);
}

bool vec2i::operator <(vec2i b)
{
    return this->x < b.x && this->y < b.y;
}

bool vec2i::operator >(vec2i b)
{
    return this->x > b.x && this->y > b.y;
}

bool vec2i::operator <=(vec2i b)
{
    return this->x <= b.x && this->y <= b.y;
}

bool vec2i::operator >=(vec2i b)
{
    return this->x >= b.x && this->y >= b.y;
}

bool vec2i::operator ==(vec2i b)
{
    return this->x == b.x && this->y == b.y;
}

bool vec2i::operator !=(vec2i b)
{
    return this->x != b.x && this->y != b.y;
}

vec2i::operator vec2()
{
    return vec2(x, y);
}

}