#pragma once
#include <stdbool.h>
#include "vectors.h"

/// things you can log with `st_log`
typedef enum {
    /// memory address
    ST_LOG_TYPE_ADDRESS = 0,
    /// int of 32
    ST_LOG_TYPE_INT32,
    /// int of 64
    ST_LOG_TYPE_INT64,
    /// int of u of 32
    ST_LOG_TYPE_UINT32,
    /// int of u of 64
    ST_LOG_TYPE_UINT64,
    /// shit float
    ST_LOG_TYPE_FLOAT32,
    /// float
    ST_LOG_TYPE_FLOAT64,
    /// character
    ST_LOG_TYPE_CHAR,
    /// string
    ST_LOG_TYPE_STRING,
    /// vector of 2
    ST_LOG_TYPE_VEC2,
    /// vector of i of 2
    ST_LOG_TYPE_VEC2I,
    /// vector of 3
    ST_LOG_TYPE_VEC3,
    /// vector of i of 3
    ST_LOG_TYPE_VEC3I,
    /// just a vec3i but formatted as a version string
    ST_LOG_TYPE_VEC3I_VERSION
} StLogType;

#ifndef ST_STARRY_VERSION
/// version of the engine
#define ST_STARRY_VERSION (stvec3i){ .x = 3, .y = 0, .z = 0 }
#endif

#ifndef ST_STARRY_VERSION_STR
/// version of the engine but as a string
#define ST_STARRY_VERSION_STR "v3.0.0"
#endif

#ifndef ST_GAME_VERSION_STR
/// game version :)
#define ST_GAME_VERSION_STR "v0.11.0"
#endif

/// initializes the core components of the engine. returns true if it succeeded, returns false otherwise
bool st_new();

/// converts common types to strings and writes them to `out`
void st_to_str(void* data, StLogType type, char* out);

/// logs common types along with a message. the ultimate debugging technique. this also flushes stdout because sometimes there's not even enough time for it to do that, it just dies (e.g. segfault)
void st_log(const char* msg, void* data, StLogType type);