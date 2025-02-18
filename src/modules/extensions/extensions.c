#include <stdio.h>
#define LUA_IMPL
#include "minilua.h"
#include "core/math/math.h"
#include "extensions.h"

lua_State* lua;

static int32 starry_deg2rad(lua_State* lua)
{
    // parameters
    float64 deg = luaL_checknumber(lua, 1);
    float64 result = st_deg2rad(deg);
    // return value
    lua_pushnumber(lua, result);
    return 1;
}

static int32 starry_rad2deg(lua_State* lua)
{
    // parameters
    float64 rad = luaL_checknumber(lua, 1);
    float64 result = st_rad2deg(rad);
    // return value
    lua_pushnumber(lua, result);
    return 1;
}

static int32 starry_random_base64(lua_State* lua)
{
    // parameters
    int64 len = luaL_checkinteger(lua, 1);
    char buf[len + 1];
    st_rand_base64((uint8)len, buf);
    // return value
    lua_pushstring(lua, buf);
    return 1;
}

static int32 starry_clamp(lua_State* lua)
{
    // parameters
    float64 val = luaL_checknumber(lua, 1);
    float64 min = luaL_checknumber(lua, 2);
    float64 max = luaL_checknumber(lua, 3);
    // return value
    lua_pushnumber(lua, st_clamp(val, min, max));
    return 1;
}

static int32 starry_vec2_add(lua_State* lua);
static int32 starry_vec2_sub(lua_State* lua);
static int32 starry_vec2_mul(lua_State* lua);
static int32 starry_vec2_div(lua_State* lua);
static int32 starry_vec2_mod(lua_State* lua);
static int32 starry_vec2_unm(lua_State* lua);
static int32 starry_vec2_eq(lua_State* lua);
static int32 starry_vec2_lt(lua_State* lua);
static int32 starry_vec2_lte(lua_State* lua);
static int32 starry_vec2_str(lua_State* lua);

static int32 starry_vec2_new(lua_State* lua)
{
    // parameters
    float64 x = luaL_checknumber(lua, 1);
    float64 y = luaL_checknumber(lua, 2);

    // man
    // 2 for the elements, 11 for the metatable methods
    lua_createtable(lua, 0, 13);

    lua_pushnumber(lua, x);
    lua_setfield(lua, -2, "x");

    lua_pushnumber(lua, y);
    lua_setfield(lua, -2, "y");
    
    lua_pushcfunction(lua, starry_vec2_add);
    lua_setfield(lua, -2, "__add");
    return 1;
}

static int32 starry_vec2_add(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    float64 x1 = luaL_checknumber(lua, 1);
    lua_getfield(lua, 1, "y");
    float64 y1 = luaL_checknumber(lua, 2);

    lua_getfield(lua, 2, "x");
    float64 x2 = luaL_checknumber(lua, 1);
    lua_getfield(lua, 2, "y");
    float64 y2 = luaL_checknumber(lua, 2);

    lua_pushnumber(lua, x1 + x2);
    lua_pushnumber(lua, y1 + y2);
    starry_vec2_new(lua);
    return 1;
}

static int32 starry_vec2_sub(lua_State* lua);
static int32 starry_vec2_mul(lua_State* lua);
static int32 starry_vec2_div(lua_State* lua);
static int32 starry_vec2_mod(lua_State* lua);
static int32 starry_vec2_unm(lua_State* lua);
static int32 starry_vec2_eq(lua_State* lua);
static int32 starry_vec2_lt(lua_State* lua);
static int32 starry_vec2_lte(lua_State* lua);
static int32 starry_vec2_str(lua_State* lua);

/// binds every function ever
static void bind()
{
    // global functions are accessed through the starry table
    lua_createtable(lua, 0, 4);

    lua_pushcfunction(lua, starry_deg2rad);
    lua_setfield(lua, -2, "deg2rad");

    lua_pushcfunction(lua, starry_rad2deg);
    lua_setfield(lua, -2, "rad2deg");

    lua_pushcfunction(lua, starry_random_base64);
    lua_setfield(lua, -2, "random_base64");

    lua_pushcfunction(lua, starry_clamp);
    lua_setfield(lua, -2, "clamp");

    // global functions are accessed through the starry table
    lua_setglobal(lua, "starry");

    // vectors
    lua_createtable(lua, 0, 1);
    lua_pushcfunction(lua, starry_vec2_new);
    lua_setfield(lua, -2, "new");
    lua_setglobal(lua, "vec2");
}

void StExtensions_new()
{
    lua = luaL_newstate();
    if (lua == NULL) {
        fprintf(stderr, "[EXTENSIONS] Couldn't initialize Lua\n");
    }
    luaL_openlibs(lua);
    printf("[EXTENSIONS] Initialized Lua\n");

    bind();
    printf("[EXTENSIONS] Lua bindings setup\n");
}

void StExtensions_free()
{
    lua_close(lua);
    printf("[EXTENSIONS] Lua is dead.\n");
}

void StExtensions_run(const char* path)
{
    luaL_dofile(lua, path);
}