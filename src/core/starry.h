#pragma once

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

/// converts common types to strings and writes them to `out`
void st_to_str(void* data, StLogType type, char* out);

/// logs common types along with a message. the ultimate debugging technique. this also flushes stdout because sometimes there's not even enough time for it to do that, it just dies (e.g. segfault)
void st_log(const char* msg, void* data, StLogType type);