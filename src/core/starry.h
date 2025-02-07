#pragma once
#include <stdbool.h>
#include "vectors.h"

/// common starry types
typedef enum {
    ST_LOG_TYPE_ADDRESS = 0,
    ST_LOG_TYPE_INT32,
    ST_LOG_TYPE_INT64,
    ST_LOG_TYPE_UINT32,
    ST_LOG_TYPE_UINT64,
    ST_LOG_TYPE_FLOAT32,
    ST_LOG_TYPE_FLOAT64,
    ST_LOG_TYPE_CHAR,
    ST_LOG_TYPE_STRING,
    ST_LOG_TYPE_VEC2,
    ST_LOG_TYPE_VEC2I,
    ST_LOG_TYPE_VEC3,
    ST_LOG_TYPE_VEC3I,
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

/// initializes the core components of the engine. returns true if it succeeded, returns false otherwise
bool st_new();

/// converts common types to strings and writes them to `out`
void st_to_str(void* data, StLogType type, char* out);

/// logs common types along with a message. the ultimate debugging technique. this also flushes stdout because sometimes there's not even enough time for it to do that, it just dies (e.g. segfault)
void st_log(const char* msg, void* data, StLogType type);