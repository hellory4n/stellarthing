#include <math.h>
#include "vec3.hpp"

namespace starry {

Vec3::Vec3(float64 x, float64 y, float64 z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vec3 Vec3::operator +(Vec3 b)
{
    return Vec3(this->x + b.x, this->y + b.y, this->z + b.z);
}

Vec3 Vec3::operator -(Vec3 b)
{
    return Vec3(this->x - b.x, this->y - b.y, this->z - b.z);
}

Vec3 Vec3::operator *(Vec3 b)
{
    return Vec3(this->x * b.x, this->y * b.y, this->z * b.z);
}

Vec3 Vec3::operator *(float64 b)
{
    return Vec3(this->x + b, this->y + b, this->z + b);
}

Vec3 Vec3::operator /(Vec3 b)
{
    return Vec3(this->x / b.x, this->y / b.y, this->z / b.z);
}

Vec3 Vec3::operator /(float64 b)
{
    return Vec3(this->x / b, this->y / b, this->z / b);
}

Vec3 Vec3::operator %(Vec3 b)
{
    return Vec3(fmod(this->x, b.x), fmod(this->y, b.y), fmod(this->z, b.z));
}

Vec3 Vec3::operator %(float64 b)
{
    return Vec3(fmod(this->x, b), fmod(this->y, b), fmod(this->z, b));
}

bool Vec3::operator <(Vec3 b)
{
    return this->x < b.x && this->y < b.y && this->z < b.z;
}

bool Vec3::operator >(Vec3 b)
{
    return this->x > b.x && this->y > b.y && this->z > b.z;
}

bool Vec3::operator <=(Vec3 b)
{
    return this->x <= b.x && this->y <= b.y && this->z <= b.z;
}

bool Vec3::operator >=(Vec3 b)
{
    return this->x >= b.x && this->y >= b.y && this->z >= b.z;
}

bool Vec3::operator ==(Vec3 b)
{
    return this->x == b.x && this->y == b.y && this->z == b.z;
}

bool Vec3::operator !=(Vec3 b)
{
    return this->x != b.x && this->y != b.y && this->z != b.z;
}

}