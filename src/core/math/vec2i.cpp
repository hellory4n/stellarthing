#include <math.h>
#include "vec2i.hpp"

namespace starry {

Vec2i::Vec2i(int64 x, int64 y)
{
    this->x = x;
    this->y = y;
}

Vec2i Vec2i::operator +(Vec2i b)
{
    return Vec2i(this->x + b.x, this->y + b.y);
}

Vec2i Vec2i::operator -(Vec2i b)
{
    return Vec2i(this->x - b.x, this->y - b.y);
}

Vec2i Vec2i::operator *(Vec2i b)
{
    return Vec2i(this->x * b.x, this->y * b.y);
}

Vec2i Vec2i::operator *(int64 b)
{
    return Vec2i(this->x * b, this->y * b);
}

Vec2i Vec2i::operator /(Vec2i b)
{
    return Vec2i(this->x / b.x, this->y / b.y);
}

Vec2i Vec2i::operator /(int64 b)
{
    return Vec2i(this->x / b, this->y / b);
}

Vec2i Vec2i::operator %(Vec2i b)
{
    return Vec2i(fmod(this->x, b.x), fmod(this->y, b.y));
}

Vec2i Vec2i::operator %(int64 b)
{
    return Vec2i(this->x % b, this->y % b);
}

bool Vec2i::operator <(Vec2i b)
{
    return this->x < b.x && this->y < b.y;
}

bool Vec2i::operator >(Vec2i b)
{
    return this->x > b.x && this->y > b.y;
}

bool Vec2i::operator <=(Vec2i b)
{
    return this->x <= b.x && this->y <= b.y;
}

bool Vec2i::operator >=(Vec2i b)
{
    return this->x >= b.x && this->y >= b.y;
}

bool Vec2i::operator ==(Vec2i b)
{
    return this->x == b.x && this->y == b.y;
}

bool Vec2i::operator !=(Vec2i b)
{
    return this->x != b.x && this->y != b.y;
}

Vec2i::operator Vec2()
{
    return Vec2(x, y);
}

}