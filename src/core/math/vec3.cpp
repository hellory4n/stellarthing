#include <math.h>
#include "vec3.hpp"

namespace starry {

vec3::vec3(float64 x, float64 y, float64 z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

vec3 vec3::operator +(vec3 b)
{
    return vec3(this->x + b.x, this->y + b.y, this->z + b.z);
}

vec3 vec3::operator -(vec3 b)
{
    return vec3(this->x - b.x, this->y - b.y, this->z - b.z);
}

vec3 vec3::operator *(vec3 b)
{
    return vec3(this->x * b.x, this->y * b.y, this->z * b.z);
}

vec3 vec3::operator *(float64 b)
{
    return vec3(this->x + b, this->y + b, this->z + b);
}

vec3 vec3::operator /(vec3 b)
{
    return vec3(this->x / b.x, this->y / b.y, this->z / b.z);
}

vec3 vec3::operator /(float64 b)
{
    return vec3(this->x / b, this->y / b, this->z / b);
}

vec3 vec3::operator %(vec3 b)
{
    return vec3(fmod(this->x, b.x), fmod(this->y, b.y), fmod(this->z, b.z));
}

vec3 vec3::operator %(float64 b)
{
    return vec3(fmod(this->x, b), fmod(this->y, b), fmod(this->z, b));
}

bool vec3::operator <(vec3 b)
{
    return this->x < b.x && this->y < b.y && this->z < b.z;
}

bool vec3::operator >(vec3 b)
{
    return this->x > b.x && this->y > b.y && this->z > b.z;
}

bool vec3::operator <=(vec3 b)
{
    return this->x <= b.x && this->y <= b.y && this->z <= b.z;
}

bool vec3::operator >=(vec3 b)
{
    return this->x >= b.x && this->y >= b.y && this->z >= b.z;
}

bool vec3::operator ==(vec3 b)
{
    return this->x == b.x && this->y == b.y && this->z == b.z;
}

bool vec3::operator !=(vec3 b)
{
    return this->x != b.x && this->y != b.y && this->z != b.z;
}

}