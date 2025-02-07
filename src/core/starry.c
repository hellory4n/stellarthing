#include <string.h>
#include <stdio.h>
#include <time.h>
#include "starry.h"

void st_to_str(void* data, StLogType type, char* out)
{
    switch (type) {
    case ST_LOG_TYPE_INT32:
        sprintf(out, "%i", (int32)data);
        break;
    case ST_LOG_TYPE_INT64:
        sprintf(out, "%li", (int64)data);
        break;
    case ST_LOG_TYPE_UINT32:
        sprintf(out, "%u", (uint32)data);
        break;
    case ST_LOG_TYPE_UINT64:
        sprintf(out, "%lu", (uint64)data);
        break;
    case ST_LOG_TYPE_FLOAT32:
        sprintf(out, "%f", *(float32*)data);
        break;
    case ST_LOG_TYPE_FLOAT64:
        sprintf(out, "%f", *(float64*)data);
        break;
    case ST_LOG_TYPE_CHAR:
        sprintf(out, "%c", (char)data);
        break;
    case ST_LOG_TYPE_STRING:
        sprintf(out, "%s", (const char*)data);
        break;
    case ST_LOG_TYPE_ADDRESS:
        sprintf(out, "%p", data);
        break;
    case ST_LOG_TYPE_VEC2:
        sprintf(out, "(%f, %f)", ((stvec2*)data)->x, ((stvec2*)data)->y);
        break;
    case ST_LOG_TYPE_VEC2I:
        sprintf(out, "(%li, %li)", ((stvec2i*)data)->x, ((stvec2i*)data)->y);
        break;
    case ST_LOG_TYPE_VEC3:
        sprintf(out, "(%f, %f, %f)", ((stvec3*)data)->x, ((stvec3*)data)->y, ((stvec3*)data)->z);
        break;
    case ST_LOG_TYPE_VEC3I:
        sprintf(out, "(%li, %li, %li)", ((stvec3i*)data)->x, ((stvec3i*)data)->y, ((stvec3i*)data)->z);
        break;
    case ST_LOG_TYPE_VEC3I_VERSION:
        sprintf(out, "v%li.%li.%li", ((stvec3i*)data)->x, ((stvec3i*)data)->y, ((stvec3i*)data)->z);
        break;
    default:
        sprintf(out, "unexpected type");
        break;
    }
}

void st_log(const char* msg, void* data, StLogType type)
{
    // THIS WILL PROBABLY BE INCONVENIENT IF YOU TRY TO PRINT A GIANT STRING
    char shia_labuffer[256];
    st_to_str(data, type, shia_labuffer);
    printf("%s: %s\n", msg, shia_labuffer);
    fflush(stdout);
}

bool st_new()
{
    printf("Initializing Starry %s\n", ST_STARRY_VERSION_STR);

    // so random!
    srand(time(NULL));

    return true;
}