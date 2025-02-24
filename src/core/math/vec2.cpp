#include <math.h>
#include "vec2.hpp"

namespace starry {

Vec2::Vec2(float64 x, float64 y)
{
    this->x = x;
    this->y = y;
}

Vec2 Vec2::operator +(Vec2 b)
{
    return Vec2(this->x + b.x, this->y + b.y);
}

Vec2 Vec2::operator -(Vec2 b)
{
    return Vec2(this->x - b.x, this->y - b.y);
}

Vec2 Vec2::operator *(Vec2 b)
{
    return Vec2(this->x * b.x, this->y * b.y);
}

Vec2 Vec2::operator *(float64 b)
{
    return Vec2(this->x * b, this->y * b);
}

Vec2 Vec2::operator /(Vec2 b)
{
    return Vec2(this->x / b.x, this->y / b.y);
}

Vec2 Vec2::operator /(float64 b)
{
    return Vec2(this->x / b, this->y / b);
}

Vec2 Vec2::operator %(Vec2 b)
{
    return Vec2(fmod(this->x, b.x), fmod(this->y, b.y));
}

Vec2 Vec2::operator %(float64 b)
{
    return Vec2(fmod(this->x, b), fmod(this->y, b));
}

bool Vec2::operator <(Vec2 b)
{
    return this->x < b.x && this->y < b.y;
}

bool Vec2::operator >(Vec2 b)
{
    return this->x > b.x && this->y > b.y;
}

bool Vec2::operator <=(Vec2 b)
{
    return this->x <= b.x && this->y <= b.y;
}

bool Vec2::operator >=(Vec2 b)
{
    return this->x >= b.x && this->y >= b.y;
}

bool Vec2::operator ==(Vec2 b)
{
    return this->x == b.x && this->y == b.y;
}

bool Vec2::operator !=(Vec2 b)
{
    return this->x != b.x && this->y != b.y;
}

}