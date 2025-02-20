#include <math.h>
#include "vec3i.hpp"

namespace starry {

vec3i::vec3i(int64 x, int64 y, int64 z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

vec3i vec3i::operator +(vec3i b)
{
    return vec3i(this->x + b.x, this->y + b.y, this->z + b.z);
}

vec3i vec3i::operator -(vec3i b)
{
    return vec3i(this->x - b.x, this->y - b.y, this->z - b.z);
}

vec3i vec3i::operator *(vec3i b)
{
    return vec3i(this->x * b.x, this->y * b.y, this->z * b.z);
}

vec3i vec3i::operator *(int64 b)
{
    return vec3i(this->x + b, this->y + b, this->z + b);
}

vec3i vec3i::operator /(vec3i b)
{
    return vec3i(this->x / b.x, this->y / b.y, this->z / b.z);
}

vec3i vec3i::operator /(int64 b)
{
    return vec3i(this->x / b, this->y / b, this->z / b);
}

vec3i vec3i::operator %(vec3i b)
{
    return vec3i(this->x % b.x, this->y % b.y, this->z % b.z);
}

vec3i vec3i::operator %(int64 b)
{
    return vec3i(this->x % b, this->y % b, this->z % b);
}

bool vec3i::operator <(vec3i b)
{
    return this->x < b.x && this->y < b.y && this->z < b.z;
}

bool vec3i::operator >(vec3i b)
{
    return this->x > b.x && this->y > b.y && this->z > b.z;
}

bool vec3i::operator <=(vec3i b)
{
    return this->x <= b.x && this->y <= b.y && this->z <= b.z;
}

bool vec3i::operator >=(vec3i b)
{
    return this->x >= b.x && this->y >= b.y && this->z >= b.z;
}

bool vec3i::operator ==(vec3i b)
{
    return this->x == b.x && this->y == b.y && this->z == b.z;
}

bool vec3i::operator !=(vec3i b)
{
    return this->x != b.x && this->y != b.y && this->z != b.z;
}

}