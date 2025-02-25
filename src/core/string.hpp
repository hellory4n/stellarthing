#ifndef ST_STRING_H
#define ST_STRING_H
#include "core/collections/array.hpp"

namespace starry {

/// immutable string of characters
class String {
private:
    Array<char> __internal = {0};
    nint __len = 0;
public:
    /// length doesn't include the null character
    String(nint len);
    /// length doesn't include the null character
    String(const char* from, nint len);
    String(const char* from);

    operator char*();

    /// converts the string to a C string
    char* cstr();
    /// gets the character at an index
    char at(nint idx);
    /// returns the length of the string, not including the null character
    nint len();

    /// pretty much just snprintf
    static String fmt(nint buffer_size, const char* format, ...);
};

}

#endif // ST_STRING_H
