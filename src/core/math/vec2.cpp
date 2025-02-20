#include <math.h>
#include "vec2.hpp"

namespace starry {

vec2::vec2(float64 x, float64 y)
{
    this->x = x;
    this->y = y;
}

vec2 vec2::operator +(vec2 b)
{
    return vec2(this->x + b.x, this->y + b.y);
}

vec2 vec2::operator -(vec2 b)
{
    return vec2(this->x - b.x, this->y - b.y);
}

vec2 vec2::operator *(vec2 b)
{
    return vec2(this->x * b.x, this->y * b.y);
}

vec2 vec2::operator *(float64 b)
{
    return vec2(this->x * b, this->y * b);
}

vec2 vec2::operator /(vec2 b)
{
    return vec2(this->x / b.x, this->y / b.y);
}

vec2 vec2::operator /(float64 b)
{
    return vec2(this->x / b, this->y / b);
}

vec2 vec2::operator %(vec2 b)
{
    return vec2(fmod(this->x, b.x), fmod(this->y, b.y));
}

vec2 vec2::operator %(float64 b)
{
    return vec2(fmod(this->x, b), fmod(this->y, b));
}

bool vec2::operator <(vec2 b)
{
    return this->x < b.x && this->y < b.y;
}

bool vec2::operator >(vec2 b)
{
    return this->x > b.x && this->y > b.y;
}

bool vec2::operator <=(vec2 b)
{
    return this->x <= b.x && this->y <= b.y;
}

bool vec2::operator >=(vec2 b)
{
    return this->x >= b.x && this->y >= b.y;
}

bool vec2::operator ==(vec2 b)
{
    return this->x == b.x && this->y == b.y;
}

bool vec2::operator !=(vec2 b)
{
    return this->x != b.x && this->y != b.y;
}

}