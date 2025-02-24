#include <math.h>
#include "vec3i.hpp"

namespace starry {

Vec3i::Vec3i(int64 x, int64 y, int64 z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vec3i Vec3i::operator +(Vec3i b)
{
    return Vec3i(this->x + b.x, this->y + b.y, this->z + b.z);
}

Vec3i Vec3i::operator -(Vec3i b)
{
    return Vec3i(this->x - b.x, this->y - b.y, this->z - b.z);
}

Vec3i Vec3i::operator *(Vec3i b)
{
    return Vec3i(this->x * b.x, this->y * b.y, this->z * b.z);
}

Vec3i Vec3i::operator *(int64 b)
{
    return Vec3i(this->x + b, this->y + b, this->z + b);
}

Vec3i Vec3i::operator /(Vec3i b)
{
    return Vec3i(this->x / b.x, this->y / b.y, this->z / b.z);
}

Vec3i Vec3i::operator /(int64 b)
{
    return Vec3i(this->x / b, this->y / b, this->z / b);
}

Vec3i Vec3i::operator %(Vec3i b)
{
    return Vec3i(this->x % b.x, this->y % b.y, this->z % b.z);
}

Vec3i Vec3i::operator %(int64 b)
{
    return Vec3i(this->x % b, this->y % b, this->z % b);
}

bool Vec3i::operator <(Vec3i b)
{
    return this->x < b.x && this->y < b.y && this->z < b.z;
}

bool Vec3i::operator >(Vec3i b)
{
    return this->x > b.x && this->y > b.y && this->z > b.z;
}

bool Vec3i::operator <=(Vec3i b)
{
    return this->x <= b.x && this->y <= b.y && this->z <= b.z;
}

bool Vec3i::operator >=(Vec3i b)
{
    return this->x >= b.x && this->y >= b.y && this->z >= b.z;
}

bool Vec3i::operator ==(Vec3i b)
{
    return this->x == b.x && this->y == b.y && this->z == b.z;
}

bool Vec3i::operator !=(Vec3i b)
{
    return this->x != b.x && this->y != b.y && this->z != b.z;
}

Vec3i::operator Vec3()
{
    return Vec3(x, y, z);
}

}