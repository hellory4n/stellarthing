#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "string.hpp"

namespace starry {

String::String(nint len)
{
    this->__internal = Array<char>(len + 1);
    this->__len = len;
}

String::String(const char* from, nint len)
{
    this->__internal = Array<char>(len + 1);
    this->__len = len;

    // copy data
    for (nint i = 0; i < len; i++) {
        *this->__internal.at(i) = from[i];
    }
    *this->__internal.at(len) = '\0';
}

String::String(const char* from)
{
    String(from, strlen(from));
}

String::operator char*()
{
    return this->cstr();
}

char* String::cstr()
{
    return this->__internal.get_buffer();
}

char String::at(nint idx)
{
    return *(this->__internal.at(idx));
}

nint String::len()
{
    return this->__len;
}

String String::fmt(nint buffer_size, const char* format, ...)
{
    String buf = String(buffer_size);
    va_list args;
    va_start(args, format);
    vsnprintf(buf.cstr(), buffer_size, format, args);
    va_end(args);
    return buf;
}

}