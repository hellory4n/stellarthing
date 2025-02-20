#ifndef ST_CORE_H
#define ST_CORE_H
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

namespace starry {

/// random "size"s everywhere would be weird. this is equivalent to an uint64 on most pcs i think
typedef size_t nint;

/// 8-bit signed integer
typedef int8_t int8;
/// 16-bit signed integer
typedef int16_t int16;
/// 32-bit signed integer
typedef int32_t int32;
/// 64-bit signed integer
typedef int64_t int64;

/// 8-bit unsigned integer
typedef uint8_t uint8;
/// 16-bit unsigned integer
typedef uint16_t uint16;
/// 32-bit unsigned integer
typedef uint32_t uint32;
/// 64-bit unsigned integer
typedef uint64_t uint64;

/// 32-bit floating point number
typedef float float32;
/// 64-bit floating point number
typedef double float64;

// os crap
#if defined(_WIN32)
    #ifndef ST_WINDOWS
        #define ST_WINDOWS
    #endif
#elif defined(__unix__)
    #ifndef ST_LINUXBSD
        #define ST_LINUXBSD
    #endif
#endif

// versions
#ifndef ST_STARRY_VERSION
/// the engine version
#define ST_STARRY_VERSION "v3.1.0"
#endif

#ifndef ST_GAME_VERSION
/// the game version
#define ST_GAME_VERSION "v0.11.0"
#endif

}

#endif // ST_CORE_H
