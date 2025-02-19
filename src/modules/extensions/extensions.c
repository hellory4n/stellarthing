#include <stdio.h>
#define LUA_IMPL
#include "minilua.h"
#include "core/math/math.h"
#include "modules/audio/audio.h"
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

static int32 starry_vec2_new(lua_State* lua)
{
    float64 x = luaL_checknumber(lua, 1);
    float64 y = luaL_checknumber(lua, 2);

    lua_newtable(lua);
    luaL_getmetatable(lua, "vec2");
    lua_setmetatable(lua, -2);

    // set x and y
    lua_pushnumber(lua, x);
    lua_setfield(lua, -2, "x");
    lua_pushnumber(lua, y);
    lua_setfield(lua, -2, "y");

    return 1;
}

static int32 starry_vec2_add(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    float64 x1 = lua_tonumber(lua, -1);
    lua_getfield(lua, 1, "y");
    float64 y1 = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "x");
    float64 x2 = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "y");
    float64 y2 = lua_tonumber(lua, -1);

    lua_newtable(lua);
    luaL_getmetatable(lua, "vec2");
    lua_setmetatable(lua, -2);

    lua_pushnumber(lua, x1 + x2);
    lua_setfield(lua, -2, "x");
    lua_pushnumber(lua, y1 + y2);
    lua_setfield(lua, -2, "y");

    return 1;
}

static int32 starry_vec2_sub(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    float64 x1 = lua_tonumber(lua, -1);
    lua_getfield(lua, 1, "y");
    float64 y1 = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "x");
    float64 x2 = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "y");
    float64 y2 = lua_tonumber(lua, -1);

    lua_newtable(lua);
    luaL_getmetatable(lua, "vec2");
    lua_setmetatable(lua, -2);

    lua_pushnumber(lua, x1 - x2);
    lua_setfield(lua, -2, "x");
    lua_pushnumber(lua, y1 - y2);
    lua_setfield(lua, -2, "y");

    return 1;
}

static int32 starry_vec2_mul(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    float64 x1 = lua_tonumber(lua, -1);
    lua_getfield(lua, 1, "y");
    float64 y1 = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "x");
    float64 x2 = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "y");
    float64 y2 = lua_tonumber(lua, -1);

    lua_newtable(lua);
    luaL_getmetatable(lua, "vec2");
    lua_setmetatable(lua, -2);

    lua_pushnumber(lua, x1 * x2);
    lua_setfield(lua, -2, "x");
    lua_pushnumber(lua, y1 * y2);
    lua_setfield(lua, -2, "y");

    return 1;
}

static int32 starry_vec2_div(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    float64 x1 = lua_tonumber(lua, -1);
    lua_getfield(lua, 1, "y");
    float64 y1 = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "x");
    float64 x2 = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "y");
    float64 y2 = lua_tonumber(lua, -1);

    lua_newtable(lua);
    luaL_getmetatable(lua, "vec2");
    lua_setmetatable(lua, -2);

    lua_pushnumber(lua, x1 / x2);
    lua_setfield(lua, -2, "x");
    lua_pushnumber(lua, y1 / y2);
    lua_setfield(lua, -2, "y");

    return 1;
}

static int32 starry_vec2_mod(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    float64 x1 = lua_tonumber(lua, -1);
    lua_getfield(lua, 1, "y");
    float64 y1 = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "x");
    float64 x2 = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "y");
    float64 y2 = lua_tonumber(lua, -1);

    lua_newtable(lua);
    luaL_getmetatable(lua, "vec2");
    lua_setmetatable(lua, -2);

    lua_pushnumber(lua, fmod(x1, x2));
    lua_setfield(lua, -2, "x");
    lua_pushnumber(lua, fmod(y1, y2));
    lua_setfield(lua, -2, "y");

    return 1;
}

static int32 starry_vec2_unm(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    float64 x = lua_tonumber(lua, -1);
    lua_getfield(lua, 1, "y");
    float64 y = lua_tonumber(lua, -1);

    lua_newtable(lua);
    luaL_getmetatable(lua, "vec2");
    lua_setmetatable(lua, -2);

    lua_pushnumber(lua, -x);
    lua_setfield(lua, -2, "x");
    lua_pushnumber(lua, -y);
    lua_setfield(lua, -2, "y");

    return 1;
}

static int32 starry_vec2_eq(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    float64 x1 = lua_tonumber(lua, -1);
    lua_getfield(lua, 1, "y");
    float64 y1 = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "x");
    float64 x2 = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "y");
    float64 y2 = lua_tonumber(lua, -1);

    lua_pushboolean(lua, x1 == x2 && y1 == y2);
    return 1;
}

static int32 starry_vec2_lt(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    float64 x1 = lua_tonumber(lua, -1);
    lua_getfield(lua, 1, "y");
    float64 y1 = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "x");
    float64 x2 = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "y");
    float64 y2 = lua_tonumber(lua, -1);

    lua_pushboolean(lua, x1 < x2 && y1 < y2);
    return 1;
}

static int32 starry_vec2_lte(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    float64 x1 = lua_tonumber(lua, -1);
    lua_getfield(lua, 1, "y");
    float64 y1 = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "x");
    float64 x2 = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "y");
    float64 y2 = lua_tonumber(lua, -1);

    lua_pushboolean(lua, x1 <= x2 && y1 <= y2);
    return 1;
}

static int32 starry_vec2_str(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    float64 x = lua_tonumber(lua, -1);
    lua_getfield(lua, 1, "y");
    float64 y = lua_tonumber(lua, -1);

    lua_pushfstring(lua, "vec2(%f, %f)", x, y);
    return 1;
}

static int32 starry_vec2i_new(lua_State* lua)
{
    int64 x = luaL_checkinteger(lua, 1);
    int64 y = luaL_checkinteger(lua, 2);

    lua_newtable(lua);
    luaL_getmetatable(lua, "vec2i");
    lua_setmetatable(lua, -2);

    // set x and y
    lua_pushinteger(lua, x);
    lua_setfield(lua, -2, "x");
    lua_pushinteger(lua, y);
    lua_setfield(lua, -2, "y");

    return 1;
}

static int32 starry_vec2i_add(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    int64 x1 = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "y");
    int64 y1 = lua_tointeger(lua, -1);
    lua_getfield(lua, 2, "x");
    int64 x2 = lua_tointeger(lua, -1);
    lua_getfield(lua, 2, "y");
    int64 y2 = lua_tointeger(lua, -1);

    lua_newtable(lua);
    luaL_getmetatable(lua, "vec2i");
    lua_setmetatable(lua, -2);

    lua_pushinteger(lua, x1 + x2);
    lua_setfield(lua, -2, "x");
    lua_pushinteger(lua, y1 + y2);
    lua_setfield(lua, -2, "y");

    return 1;
}

static int32 starry_vec2i_sub(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    int64 x1 = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "y");
    int64 y1 = lua_tointeger(lua, -1);
    lua_getfield(lua, 2, "x");
    int64 x2 = lua_tointeger(lua, -1);
    lua_getfield(lua, 2, "y");
    int64 y2 = lua_tointeger(lua, -1);

    lua_newtable(lua);
    luaL_getmetatable(lua, "vec2i");
    lua_setmetatable(lua, -2);

    lua_pushinteger(lua, x1 - x2);
    lua_setfield(lua, -2, "x");
    lua_pushinteger(lua, y1 - y2);
    lua_setfield(lua, -2, "y");

    return 1;
}

static int32 starry_vec2i_mul(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    int64 x1 = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "y");
    int64 y1 = lua_tointeger(lua, -1);
    lua_getfield(lua, 2, "x");
    int64 x2 = lua_tointeger(lua, -1);
    lua_getfield(lua, 2, "y");
    int64 y2 = lua_tointeger(lua, -1);

    lua_newtable(lua);
    luaL_getmetatable(lua, "vec2i");
    lua_setmetatable(lua, -2);

    lua_pushinteger(lua, x1 * x2);
    lua_setfield(lua, -2, "x");
    lua_pushinteger(lua, y1 * y2);
    lua_setfield(lua, -2, "y");

    return 1;
}

static int32 starry_vec2i_div(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    int64 x1 = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "y");
    int64 y1 = lua_tointeger(lua, -1);
    lua_getfield(lua, 2, "x");
    int64 x2 = lua_tointeger(lua, -1);
    lua_getfield(lua, 2, "y");
    int64 y2 = lua_tointeger(lua, -1);

    lua_newtable(lua);
    luaL_getmetatable(lua, "vec2i");
    lua_setmetatable(lua, -2);

    lua_pushinteger(lua, x1 / x2);
    lua_setfield(lua, -2, "x");
    lua_pushinteger(lua, y1 / y2);
    lua_setfield(lua, -2, "y");

    return 1;
}

static int32 starry_vec2i_mod(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    int64 x1 = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "y");
    int64 y1 = lua_tointeger(lua, -1);
    lua_getfield(lua, 2, "x");
    int64 x2 = lua_tointeger(lua, -1);
    lua_getfield(lua, 2, "y");
    int64 y2 = lua_tointeger(lua, -1);

    lua_newtable(lua);
    luaL_getmetatable(lua, "vec2i");
    lua_setmetatable(lua, -2);

    lua_pushinteger(lua, x1 % x2);
    lua_setfield(lua, -2, "x");
    lua_pushinteger(lua, y1 % y2);
    lua_setfield(lua, -2, "y");

    return 1;
}

static int32 starry_vec2i_unm(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    int64 x = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "y");
    int64 y = lua_tointeger(lua, -1);

    lua_newtable(lua);
    luaL_getmetatable(lua, "vec2i");
    lua_setmetatable(lua, -2);

    lua_pushinteger(lua, -x);
    lua_setfield(lua, -2, "x");
    lua_pushinteger(lua, -y);
    lua_setfield(lua, -2, "y");

    return 1;
}

static int32 starry_vec2i_eq(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    float64 x1 = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "y");
    float64 y1 = lua_tointeger(lua, -1);
    lua_getfield(lua, 2, "x");
    float64 x2 = lua_tointeger(lua, -1);
    lua_getfield(lua, 2, "y");
    float64 y2 = lua_tointeger(lua, -1);

    lua_pushboolean(lua, x1 == x2 && y1 == y2);
    return 1;
}

static int32 starry_vec2i_lt(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    float64 x1 = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "y");
    float64 y1 = lua_tointeger(lua, -1);
    lua_getfield(lua, 2, "x");
    float64 x2 = lua_tointeger(lua, -1);
    lua_getfield(lua, 2, "y");
    float64 y2 = lua_tointeger(lua, -1);

    lua_pushboolean(lua, x1 < x2 && y1 < y2);
    return 1;
}

static int32 starry_vec2i_lte(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    float64 x1 = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "y");
    float64 y1 = lua_tointeger(lua, -1);
    lua_getfield(lua, 2, "x");
    float64 x2 = lua_tointeger(lua, -1);
    lua_getfield(lua, 2, "y");
    float64 y2 = lua_tointeger(lua, -1);

    lua_pushboolean(lua, x1 <= x2 && y1 <= y2);
    return 1;
}

static int32 starry_vec2i_str(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    int64 x = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "y");
    int64 y = lua_tointeger(lua, -1);

    lua_pushfstring(lua, "vec2i(%d, %d)", x, y);
    return 1;
}

static int32 starry_vec3_new(lua_State* lua)
{
    float64 x = luaL_checknumber(lua, 1);
    float64 y = luaL_checknumber(lua, 2);
    float64 z = luaL_checknumber(lua, 3);

    lua_newtable(lua);
    luaL_getmetatable(lua, "vec3");
    lua_setmetatable(lua, -2);

    // set x and y and z
    lua_pushnumber(lua, x);
    lua_setfield(lua, -2, "x");
    lua_pushnumber(lua, y);
    lua_setfield(lua, -2, "y");
    lua_pushnumber(lua, z);
    lua_setfield(lua, -2, "z");

    return 1;
}

static int32 starry_vec3_add(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    float64 x1 = lua_tonumber(lua, -1);
    lua_getfield(lua, 1, "y");
    float64 y1 = lua_tonumber(lua, -1);
    lua_getfield(lua, 1, "z");
    float64 z1 = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "x");
    float64 x2 = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "y");
    float64 y2 = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "z");
    float64 z2 = lua_tonumber(lua, -1);

    lua_newtable(lua);
    luaL_getmetatable(lua, "vec3");
    lua_setmetatable(lua, -2);

    lua_pushnumber(lua, x1 + x2 );
    lua_setfield(lua, -2, "x");
    lua_pushnumber(lua, y1 + y2);
    lua_setfield(lua, -2, "y");
    lua_pushnumber(lua, z1 + z2);
    lua_setfield(lua, -2, "z");

    return 1;
}

static int32 starry_vec3_sub(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    float64 x1 = lua_tonumber(lua, -1);
    lua_getfield(lua, 1, "y");
    float64 y1 = lua_tonumber(lua, -1);
    lua_getfield(lua, 1, "z");
    float64 z1 = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "x");
    float64 x2 = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "y");
    float64 y2 = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "z");
    float64 z2 = lua_tonumber(lua, -1);

    lua_newtable(lua);
    luaL_getmetatable(lua, "vec3");
    lua_setmetatable(lua, -2);

    lua_pushnumber(lua, x1 - x2 );
    lua_setfield(lua, -2, "x");
    lua_pushnumber(lua, y1 - y2);
    lua_setfield(lua, -2, "y");
    lua_pushnumber(lua, z1 - z2);
    lua_setfield(lua, -2, "z");

    return 1;
}

static int32 starry_vec3_mul(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    float64 x1 = lua_tonumber(lua, -1);
    lua_getfield(lua, 1, "y");
    float64 y1 = lua_tonumber(lua, -1);
    lua_getfield(lua, 1, "z");
    float64 z1 = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "x");
    float64 x2 = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "y");
    float64 y2 = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "z");
    float64 z2 = lua_tonumber(lua, -1);

    lua_newtable(lua);
    luaL_getmetatable(lua, "vec3");
    lua_setmetatable(lua, -2);

    lua_pushnumber(lua, x1 * x2 );
    lua_setfield(lua, -2, "x");
    lua_pushnumber(lua, y1 * y2);
    lua_setfield(lua, -2, "y");
    lua_pushnumber(lua, z1 * z2);
    lua_setfield(lua, -2, "z");

    return 1;
}

static int32 starry_vec3_div(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    float64 x1 = lua_tonumber(lua, -1);
    lua_getfield(lua, 1, "y");
    float64 y1 = lua_tonumber(lua, -1);
    lua_getfield(lua, 1, "z");
    float64 z1 = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "x");
    float64 x2 = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "y");
    float64 y2 = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "z");
    float64 z2 = lua_tonumber(lua, -1);

    lua_newtable(lua);
    luaL_getmetatable(lua, "vec3");
    lua_setmetatable(lua, -2);

    lua_pushnumber(lua, x1 / x2 );
    lua_setfield(lua, -2, "x");
    lua_pushnumber(lua, y1 / y2);
    lua_setfield(lua, -2, "y");
    lua_pushnumber(lua, z1 / z2);
    lua_setfield(lua, -2, "z");

    return 1;
}

static int32 starry_vec3_mod(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    float64 x1 = lua_tonumber(lua, -1);
    lua_getfield(lua, 1, "y");
    float64 y1 = lua_tonumber(lua, -1);
    lua_getfield(lua, 1, "z");
    float64 z1 = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "x");
    float64 x2 = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "y");
    float64 y2 = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "z");
    float64 z2 = lua_tonumber(lua, -1);

    lua_newtable(lua);
    luaL_getmetatable(lua, "vec3");
    lua_setmetatable(lua, -2);

    lua_pushnumber(lua, fmod(x1, x2));
    lua_setfield(lua, -2, "x");
    lua_pushnumber(lua, fmod(y1, y2));
    lua_setfield(lua, -2, "y");
    lua_pushnumber(lua, fmod(z1, z2));
    lua_setfield(lua, -2, "z");

    return 1;
}

static int32 starry_vec3_unm(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    float64 x = lua_tonumber(lua, -1);
    lua_getfield(lua, 1, "y");
    float64 y = lua_tonumber(lua, -1);
    lua_getfield(lua, 1, "z");
    float64 z = lua_tonumber(lua, -1);

    lua_newtable(lua);
    luaL_getmetatable(lua, "vec3");
    lua_setmetatable(lua, -2);

    lua_pushnumber(lua, -x);
    lua_setfield(lua, -2, "x");
    lua_pushnumber(lua, -y);
    lua_setfield(lua, -2, "y");
    lua_pushnumber(lua, -z);
    lua_setfield(lua, -2, "z");

    return 1;
}

static int32 starry_vec3_eq(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    float64 x1 = lua_tonumber(lua, -1);
    lua_getfield(lua, 1, "y");
    float64 y1 = lua_tonumber(lua, -1);
    lua_getfield(lua, 1, "z");
    float64 z1 = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "x");
    float64 x2 = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "y");
    float64 y2 = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "z");
    float64 z2 = lua_tonumber(lua, -1);

    lua_pushboolean(lua, x1 == x2 && y1 == y2 && z1 == z2);
    return 1;
}

static int32 starry_vec3_lt(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    float64 x1 = lua_tonumber(lua, -1);
    lua_getfield(lua, 1, "y");
    float64 y1 = lua_tonumber(lua, -1);
    lua_getfield(lua, 1, "z");
    float64 z1 = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "x");
    float64 x2 = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "y");
    float64 y2 = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "z");
    float64 z2 = lua_tonumber(lua, -1);

    lua_pushboolean(lua, x1 < x2 && y1 < y2 && z1 < z2);
    return 1;
}

static int32 starry_vec3_lte(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    float64 x1 = lua_tonumber(lua, -1);
    lua_getfield(lua, 1, "y");
    float64 y1 = lua_tonumber(lua, -1);
    lua_getfield(lua, 1, "z");
    float64 z1 = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "x");
    float64 x2 = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "y");
    float64 y2 = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "z");
    float64 z2 = lua_tonumber(lua, -1);

    lua_pushboolean(lua, x1 <= x2 && y1 <= y2 && z1 <= z2);
    return 1;
}

static int32 starry_vec3_str(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    float64 x = lua_tonumber(lua, -1);
    lua_getfield(lua, 1, "y");
    float64 y = lua_tonumber(lua, -1);
    lua_getfield(lua, 1, "z");
    float64 z = lua_tonumber(lua, -1);

    lua_pushfstring(lua, "vec3(%f, %f, %f)", x, y, z);
    return 1;
}

static int32 starry_vec3i_new(lua_State* lua)
{
    int64 x = luaL_checkinteger(lua, 1);
    int64 y = luaL_checkinteger(lua, 2);
    int64 z = luaL_checkinteger(lua, 3);

    lua_newtable(lua);
    luaL_getmetatable(lua, "vec3i");
    lua_setmetatable(lua, -2);

    // set x and y
    lua_pushinteger(lua, x);
    lua_setfield(lua, -2, "x");
    lua_pushinteger(lua, y);
    lua_setfield(lua, -2, "y");
    lua_pushinteger(lua, z);
    lua_setfield(lua, -2, "z");

    return 1;
}

static int32 starry_vec3i_add(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    int64 x1 = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "y");
    int64 y1 = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "z");
    int64 z1 = lua_tointeger(lua, -1);
    lua_getfield(lua, 2, "x");
    int64 x2 = lua_tointeger(lua, -1);
    lua_getfield(lua, 2, "y");
    int64 y2 = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "z");
    int64 z2 = lua_tointeger(lua, -1);

    lua_newtable(lua);
    luaL_getmetatable(lua, "vec3i");
    lua_setmetatable(lua, -2);

    lua_pushinteger(lua, x1 + x2);
    lua_setfield(lua, -2, "x");
    lua_pushinteger(lua, y1 + y2);
    lua_setfield(lua, -2, "y");
    lua_pushinteger(lua, z1 + z2);
    lua_setfield(lua, -2, "z");

    return 1;
}

static int32 starry_vec3i_sub(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    int64 x1 = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "y");
    int64 y1 = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "z");
    int64 z1 = lua_tointeger(lua, -1);
    lua_getfield(lua, 2, "x");
    int64 x2 = lua_tointeger(lua, -1);
    lua_getfield(lua, 2, "y");
    int64 y2 = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "z");
    int64 z2 = lua_tointeger(lua, -1);

    lua_newtable(lua);
    luaL_getmetatable(lua, "vec3i");
    lua_setmetatable(lua, -2);

    lua_pushinteger(lua, x1 - x2);
    lua_setfield(lua, -2, "x");
    lua_pushinteger(lua, y1 - y2);
    lua_setfield(lua, -2, "y");
    lua_pushinteger(lua, z1 - z2);
    lua_setfield(lua, -2, "z");

    return 1;
}

static int32 starry_vec3i_mul(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    int64 x1 = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "y");
    int64 y1 = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "z");
    int64 z1 = lua_tointeger(lua, -1);
    lua_getfield(lua, 2, "x");
    int64 x2 = lua_tointeger(lua, -1);
    lua_getfield(lua, 2, "y");
    int64 y2 = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "z");
    int64 z2 = lua_tointeger(lua, -1);

    lua_newtable(lua);
    luaL_getmetatable(lua, "vec3i");
    lua_setmetatable(lua, -2);

    lua_pushinteger(lua, x1 * x2);
    lua_setfield(lua, -2, "x");
    lua_pushinteger(lua, y1 * y2);
    lua_setfield(lua, -2, "y");
    lua_pushinteger(lua, z1 * z2);
    lua_setfield(lua, -2, "z");

    return 1;
}

static int32 starry_vec3i_div(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    int64 x1 = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "y");
    int64 y1 = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "z");
    int64 z1 = lua_tointeger(lua, -1);
    lua_getfield(lua, 2, "x");
    int64 x2 = lua_tointeger(lua, -1);
    lua_getfield(lua, 2, "y");
    int64 y2 = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "z");
    int64 z2 = lua_tointeger(lua, -1);

    lua_newtable(lua);
    luaL_getmetatable(lua, "vec3i");
    lua_setmetatable(lua, -2);

    lua_pushinteger(lua, x1 / x2);
    lua_setfield(lua, -2, "x");
    lua_pushinteger(lua, y1 / y2);
    lua_setfield(lua, -2, "y");
    lua_pushinteger(lua, z1 / z2);
    lua_setfield(lua, -2, "z");

    return 1;
}

static int32 starry_vec3i_mod(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    int64 x1 = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "y");
    int64 y1 = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "z");
    int64 z1 = lua_tointeger(lua, -1);
    lua_getfield(lua, 2, "x");
    int64 x2 = lua_tointeger(lua, -1);
    lua_getfield(lua, 2, "y");
    int64 y2 = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "z");
    int64 z2 = lua_tointeger(lua, -1);

    lua_newtable(lua);
    luaL_getmetatable(lua, "vec3i");
    lua_setmetatable(lua, -2);

    lua_pushinteger(lua, x1 % x2);
    lua_setfield(lua, -2, "x");
    lua_pushinteger(lua, y1 % y2);
    lua_setfield(lua, -2, "y");
    lua_pushinteger(lua, z1 % z2);
    lua_setfield(lua, -2, "z");

    return 1;
}

static int32 starry_vec3i_unm(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    int64 x = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "y");
    int64 y = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "z");
    int64 z = lua_tointeger(lua, -1);

    lua_newtable(lua);
    luaL_getmetatable(lua, "vec3i");
    lua_setmetatable(lua, -2);

    lua_pushinteger(lua, -x);
    lua_setfield(lua, -2, "x");
    lua_pushinteger(lua, -y);
    lua_setfield(lua, -2, "y");
    lua_pushinteger(lua, -z);
    lua_setfield(lua, -2, "z");

    return 1;
}

static int32 starry_vec3i_eq(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    int64 x1 = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "y");
    int64 y1 = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "z");
    int64 z1 = lua_tointeger(lua, -1);
    lua_getfield(lua, 2, "x");
    int64 x2 = lua_tointeger(lua, -1);
    lua_getfield(lua, 2, "y");
    int64 y2 = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "z");
    int64 z2 = lua_tointeger(lua, -1);

    lua_pushboolean(lua, x1 == x2 && y1 == y2 && z1 == z2);
    return 1;
}

static int32 starry_vec3i_lt(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    int64 x1 = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "y");
    int64 y1 = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "z");
    int64 z1 = lua_tointeger(lua, -1);
    lua_getfield(lua, 2, "x");
    int64 x2 = lua_tointeger(lua, -1);
    lua_getfield(lua, 2, "y");
    int64 y2 = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "z");
    int64 z2 = lua_tointeger(lua, -1);

    lua_pushboolean(lua, x1 < x2 && y1 < y2 && z1 < z2);
    return 1;
}

static int32 starry_vec3i_lte(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    int64 x1 = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "y");
    int64 y1 = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "z");
    int64 z1 = lua_tointeger(lua, -1);
    lua_getfield(lua, 2, "x");
    int64 x2 = lua_tointeger(lua, -1);
    lua_getfield(lua, 2, "y");
    int64 y2 = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "z");
    int64 z2 = lua_tointeger(lua, -1);

    lua_pushboolean(lua, x1 <= x2 && y1 <= y2 && z1 <= z2);
    return 1;
}

static int32 starry_vec3i_str(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    int64 x = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "y");
    int64 y = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "z");
    int64 z = lua_tointeger(lua, -1);

    lua_pushfstring(lua, "vec3i(%d, %d, %d)", x, y, z);
    return 1;
}

static int32 starry_color_rgba(lua_State* lua)
{
    int64 r = luaL_checkinteger(lua, 1);
    int64 g = luaL_checkinteger(lua, 2);
    int64 b = luaL_checkinteger(lua, 3);
    int64 a = luaL_checkinteger(lua, 4);

    lua_newtable(lua);
    luaL_getmetatable(lua, "color");
    lua_setmetatable(lua, -2);

    lua_pushinteger(lua, r);
    lua_setfield(lua, -2, "r");
    lua_pushinteger(lua, g);
    lua_setfield(lua, -2, "g");
    lua_pushinteger(lua, b);
    lua_setfield(lua, -2, "b");
    lua_pushinteger(lua, a);
    lua_setfield(lua, -2, "a");

    return 1;
}

static int32 starry_color_rgb(lua_State* lua)
{
    int64 r = luaL_checkinteger(lua, 1);
    int64 g = luaL_checkinteger(lua, 2);
    int64 b = luaL_checkinteger(lua, 3);

    lua_newtable(lua);
    luaL_getmetatable(lua, "color");
    lua_setmetatable(lua, -2);

    lua_pushinteger(lua, r);
    lua_setfield(lua, -2, "r");
    lua_pushinteger(lua, g);
    lua_setfield(lua, -2, "g");
    lua_pushinteger(lua, b);
    lua_setfield(lua, -2, "b");
    lua_pushinteger(lua, 255);
    lua_setfield(lua, -2, "a");

    return 1;
}

static int32 starry_color_str(lua_State* lua)
{
    lua_getfield(lua, 1, "r");
    int64 r = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "g");
    int64 g = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "b");
    int64 b = lua_tointeger(lua, -1);
    lua_getfield(lua, 1, "a");
    int64 a = lua_tointeger(lua, -1);

    lua_pushfstring(lua, "color(%d, %d, %d, %d)", r, g, b, a);
    return 1;
}

static int32 starry_audio_new(lua_State* lua)
{
    const char* path = luaL_checkstring(lua, 1);

    lua_newtable(lua);
    luaL_getmetatable(lua, "Audio");
    lua_setmetatable(lua, -2);

    lua_pushstring(lua, path);
    lua_setfield(lua, -2, "path");

    StAudio_new(path);
    return 1;
}

static int32 starry_audio_play(lua_State* lua)
{
    lua_getfield(lua, 1, "path");
    const char* path = lua_tostring(lua, -1);
    StAudio_play(path);
    return 1;
}

static int32 starry_audio_pause(lua_State* lua)
{
    lua_getfield(lua, 1, "path");
    const char* path = lua_tostring(lua, -1);
    bool boo = lua_toboolean(lua, 2);
    StAudio_pause(path, boo);
    return 1;
}

static int32 starry_audio_stop(lua_State* lua)
{
    lua_getfield(lua, 1, "path");
    const char* path = lua_tostring(lua, -1);
    StAudio_stop(path);
    return 1;
}

static int32 starry_audio_set_pan(lua_State* lua)
{
    lua_getfield(lua, 1, "path");
    const char* path = lua_tostring(lua, -1);
    float64 pan = luaL_checknumber(lua, 2);
    StAudio_set_pan(path, pan);
    return 1;
}

static int32 starry_audio_set_vol(lua_State* lua)
{
    lua_getfield(lua, 1, "path");
    const char* path = lua_tostring(lua, -1);
    float64 vol = luaL_checknumber(lua, 2);
    StAudio_set_volume(path, vol);
    return 1;
}

static int32 starry_audio_set_position(lua_State* lua)
{
    lua_getfield(lua, 1, "path");
    const char* path = lua_tostring(lua, -1);

    lua_getfield(lua, 2, "x");
    float64 x = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "y");
    float64 y = lua_tonumber(lua, -1);
    lua_getfield(lua, 2, "z");
    float64 z = lua_tonumber(lua, -1);
    StAudio_set_position(path, (stvec3){x, y, z});
    return 1;
}

static int32 starry_audio_set_listener(lua_State* lua)
{
    lua_getfield(lua, 1, "x");
    float64 x = lua_tonumber(lua, -1);
    lua_getfield(lua, 1, "y");
    float64 y = lua_tonumber(lua, -1);
    lua_getfield(lua, 1, "z");
    float64 z = lua_tonumber(lua, -1);
    StAudio_set_listener((stvec3){x, y, z});
    return 1;
}

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

    // vec2 metatable
    luaL_newmetatable(lua, "vec2");
    
    lua_pushnumber(lua, 0);
    lua_setfield(lua, -2, "x");

    lua_pushnumber(lua, 0);
    lua_setfield(lua, -2, "y");

    lua_pushcfunction(lua, starry_vec2_str);
    lua_setfield(lua, -2, "__tostring");

    lua_pushcfunction(lua, starry_vec2_add);
    lua_setfield(lua, -2, "__add");

    lua_pushcfunction(lua, starry_vec2_sub);
    lua_setfield(lua, -2, "__sub");
    
    lua_pushcfunction(lua, starry_vec2_mul);
    lua_setfield(lua, -2, "__mul");
    
    lua_pushcfunction(lua, starry_vec2_div);
    lua_setfield(lua, -2, "__div");

    lua_pushcfunction(lua, starry_vec2_mod);
    lua_setfield(lua, -2, "__mod");

    lua_pushcfunction(lua, starry_vec2_unm);
    lua_setfield(lua, -2, "__unm");

    lua_pushcfunction(lua, starry_vec2_eq);
    lua_setfield(lua, -2, "__eq");

    lua_pushcfunction(lua, starry_vec2_lt);
    lua_setfield(lua, -2, "__lt");

    lua_pushcfunction(lua, starry_vec2_lte);
    lua_setfield(lua, -2, "__le");

    lua_pop(lua, 1);

    // vec2 constructor
    lua_pushcfunction(lua, starry_vec2_new);
    lua_setglobal(lua, "vec2");

    // vec2i metatable
    luaL_newmetatable(lua, "vec2i");
    
    lua_pushnumber(lua, 0);
    lua_setfield(lua, -2, "x");

    lua_pushnumber(lua, 0);
    lua_setfield(lua, -2, "y");

    lua_pushcfunction(lua, starry_vec2i_str);
    lua_setfield(lua, -2, "__tostring");

    lua_pushcfunction(lua, starry_vec2i_add);
    lua_setfield(lua, -2, "__add");

    lua_pushcfunction(lua, starry_vec2i_sub);
    lua_setfield(lua, -2, "__sub");
    
    lua_pushcfunction(lua, starry_vec2i_mul);
    lua_setfield(lua, -2, "__mul");
    
    lua_pushcfunction(lua, starry_vec2i_div);
    lua_setfield(lua, -2, "__div");

    lua_pushcfunction(lua, starry_vec2i_mod);
    lua_setfield(lua, -2, "__mod");

    lua_pushcfunction(lua, starry_vec2i_unm);
    lua_setfield(lua, -2, "__unm");

    lua_pushcfunction(lua, starry_vec2i_eq);
    lua_setfield(lua, -2, "__eq");

    lua_pushcfunction(lua, starry_vec2i_lt);
    lua_setfield(lua, -2, "__lt");

    lua_pushcfunction(lua, starry_vec2i_lte);
    lua_setfield(lua, -2, "__le");

    lua_pop(lua, 1);

    // vec2i constructor
    lua_pushcfunction(lua, starry_vec2i_new);
    lua_setglobal(lua, "vec2i");

    // vec3 metatable
    luaL_newmetatable(lua, "vec3");
    
    lua_pushnumber(lua, 0);
    lua_setfield(lua, -2, "x");

    lua_pushnumber(lua, 0);
    lua_setfield(lua, -2, "y");

    lua_pushnumber(lua, 0);
    lua_setfield(lua, -2, "z");

    lua_pushcfunction(lua, starry_vec3_str);
    lua_setfield(lua, -2, "__tostring");

    lua_pushcfunction(lua, starry_vec3_add);
    lua_setfield(lua, -2, "__add");

    lua_pushcfunction(lua, starry_vec3_sub);
    lua_setfield(lua, -2, "__sub");
    
    lua_pushcfunction(lua, starry_vec3_mul);
    lua_setfield(lua, -2, "__mul");
    
    lua_pushcfunction(lua, starry_vec3_div);
    lua_setfield(lua, -2, "__div");

    lua_pushcfunction(lua, starry_vec3_mod);
    lua_setfield(lua, -2, "__mod");

    lua_pushcfunction(lua, starry_vec3_unm);
    lua_setfield(lua, -2, "__unm");

    lua_pushcfunction(lua, starry_vec3_eq);
    lua_setfield(lua, -2, "__eq");

    lua_pushcfunction(lua, starry_vec3_lt);
    lua_setfield(lua, -2, "__lt");

    lua_pushcfunction(lua, starry_vec3_lte);
    lua_setfield(lua, -2, "__le");

    lua_pop(lua, 1);

    // vec3 constructor
    lua_pushcfunction(lua, starry_vec3_new);
    lua_setglobal(lua, "vec3");

    // vec3i metatable
    luaL_newmetatable(lua, "vec3i");
    
    lua_pushnumber(lua, 0);
    lua_setfield(lua, -2, "x");

    lua_pushnumber(lua, 0);
    lua_setfield(lua, -2, "y");

    lua_pushnumber(lua, 0);
    lua_setfield(lua, -2, "z");

    lua_pushcfunction(lua, starry_vec3i_str);
    lua_setfield(lua, -2, "__tostring");

    lua_pushcfunction(lua, starry_vec3i_add);
    lua_setfield(lua, -2, "__add");

    lua_pushcfunction(lua, starry_vec3i_sub);
    lua_setfield(lua, -2, "__sub");
    
    lua_pushcfunction(lua, starry_vec3i_mul);
    lua_setfield(lua, -2, "__mul");
    
    lua_pushcfunction(lua, starry_vec3i_div);
    lua_setfield(lua, -2, "__div");

    lua_pushcfunction(lua, starry_vec3i_mod);
    lua_setfield(lua, -2, "__mod");

    lua_pushcfunction(lua, starry_vec3i_unm);
    lua_setfield(lua, -2, "__unm");

    lua_pushcfunction(lua, starry_vec3i_eq);
    lua_setfield(lua, -2, "__eq");

    lua_pushcfunction(lua, starry_vec3i_lt);
    lua_setfield(lua, -2, "__lt");

    lua_pushcfunction(lua, starry_vec3i_lte);
    lua_setfield(lua, -2, "__le");

    lua_pop(lua, 1);

    // vec3i constructor
    lua_pushcfunction(lua, starry_vec3i_new);
    lua_setglobal(lua, "vec3i");

    // color metatable
    luaL_newmetatable(lua, "color");
    
    lua_pushnumber(lua, 0);
    lua_setfield(lua, -2, "r");

    lua_pushnumber(lua, 0);
    lua_setfield(lua, -2, "g");

    lua_pushnumber(lua, 0);
    lua_setfield(lua, -2, "b");

    lua_pushnumber(lua, 0);
    lua_setfield(lua, -2, "a");

    lua_pushcfunction(lua, starry_color_str);
    lua_setfield(lua, -2, "__tostring");

    lua_pop(lua, 1);

    // color constructors
    lua_pushcfunction(lua, starry_color_rgba);
    lua_setglobal(lua, "rgba");

    lua_pushcfunction(lua, starry_color_rgb);
    lua_setglobal(lua, "rgb");

    // color constants
    lua_newtable(lua);
    luaL_getmetatable(lua, "color");
    lua_setmetatable(lua, -2);
    lua_pushinteger(lua, 255);
    lua_setfield(lua, -2, "r");
    lua_pushinteger(lua, 255);
    lua_setfield(lua, -2, "g");
    lua_pushinteger(lua, 255);
    lua_setfield(lua, -2, "b");
    lua_pushinteger(lua, 255);
    lua_setfield(lua, -2, "a");
    lua_setglobal(lua, "COLOR_WHITE");

    lua_newtable(lua);
    luaL_getmetatable(lua, "color");
    lua_setmetatable(lua, -2);
    lua_pushinteger(lua, 0);
    lua_setfield(lua, -2, "r");
    lua_pushinteger(lua, 0);
    lua_setfield(lua, -2, "g");
    lua_pushinteger(lua, 0);
    lua_setfield(lua, -2, "b");
    lua_pushinteger(lua, 255);
    lua_setfield(lua, -2, "a");
    lua_setglobal(lua, "COLOR_BLACK");

    lua_newtable(lua);
    luaL_getmetatable(lua, "color");
    lua_setmetatable(lua, -2);
    lua_pushinteger(lua, 0);
    lua_setfield(lua, -2, "r");
    lua_pushinteger(lua, 0);
    lua_setfield(lua, -2, "g");
    lua_pushinteger(lua, 0);
    lua_setfield(lua, -2, "b");
    lua_pushinteger(lua, 0);
    lua_setfield(lua, -2, "a");
    lua_setglobal(lua, "COLOR_TRANSPARENT");

    // audio metatable
    luaL_newmetatable(lua, "Audio");
    
    lua_pushstring(lua, "");
    lua_setfield(lua, -2, "path");

    lua_pushcfunction(lua, starry_audio_pause);
    lua_setfield(lua, -2, "pause");

    lua_pushcfunction(lua, starry_audio_play);
    lua_setfield(lua, -2, "play");

    lua_pushcfunction(lua, starry_audio_stop);
    lua_setfield(lua, -2, "stop");

    lua_pushcfunction(lua, starry_audio_set_pan);
    lua_setfield(lua, -2, "set_pan");
    
    lua_pushcfunction(lua, starry_audio_set_vol);
    lua_setfield(lua, -2, "set_volume");

    lua_pushcfunction(lua, starry_audio_set_position);
    lua_setfield(lua, -2, "set_position");

    lua_pop(lua, 1);

    // Audio static functions
    lua_createtable(lua, 0, 4);

    lua_pushcfunction(lua, starry_audio_new);
    lua_setfield(lua, -2, "new");

    lua_pushcfunction(lua, starry_audio_set_listener);
    lua_setfield(lua, -2, "set_listener");

    lua_setglobal(lua, "Audio");
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
    if (luaL_dofile(lua, path)) {
        fprintf(stderr, "[EXTENSIONS] Lua error: %s\n", lua_tostring(lua, -1));
    }
}