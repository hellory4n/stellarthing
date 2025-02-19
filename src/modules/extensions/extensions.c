#include <stdio.h>
#define LUA_IMPL
#include "minilua.h"
#include "core/math/math.h"
#include "modules/graphics/graphics.h"
#include "modules/graphics/tilemap.h"
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

static int32 starry_load_texture(lua_State* lua)
{
    const char* path = luaL_checkstring(lua, 1);
    // future calls are gonna be cached
    StTexture_new(path);
    lua_pushstring(lua, path);
    return 1;
}

static int32 starry_draw_texture(lua_State* lua)
{
    const char* path = luaL_checkstring(lua, 1);
    float64 x = luaL_checknumber(lua, 2);
    float64 y = luaL_checknumber(lua, 3);
    float64 rotation = luaL_checknumber(lua, 4);

    // future calls are gonna be cached
    StTexture* texture = StTexture_new(path);
    StGraphics_draw_texture(texture, (stvec2){x, y}, rotation);
    return 1;
}

static int32 starry_draw_texture_ext(lua_State* lua)
{
    const char* path = luaL_checkstring(lua, 1);
    float64 src_pos_x = luaL_checknumber(lua, 2);
    float64 src_pos_y = luaL_checknumber(lua, 3);
    float64 src_size_x = luaL_checknumber(lua, 4);
    float64 src_size_y = luaL_checknumber(lua, 5);
    float64 dst_pos_x = luaL_checknumber(lua, 6);
    float64 dst_pos_y = luaL_checknumber(lua, 7);
    float64 dst_size_x = luaL_checknumber(lua, 8);
    float64 dst_size_y = luaL_checknumber(lua, 9);
    float64 origin_x = luaL_checknumber(lua, 10);
    float64 origin_y = luaL_checknumber(lua, 11);
    float64 rotation = luaL_checknumber(lua, 12);
    int64 tint_r = luaL_checkinteger(lua, 13);
    int64 tint_g = luaL_checkinteger(lua, 14);
    int64 tint_b = luaL_checkinteger(lua, 15);
    int64 tint_a = luaL_checkinteger(lua, 16);

    // future calls are gonna be cached
    StTexture* texture = StTexture_new(path);
    StGraphics_draw_texture_ext(
        texture,
        (stvec2){src_pos_x, src_pos_y},
        (stvec2){src_size_x, src_size_y},
        (stvec2){dst_pos_x, dst_pos_y},
        (stvec2){dst_size_x, dst_size_y},
        (stvec2){origin_x, origin_y},
        rotation,
        (stcolor){tint_r, tint_g, tint_b, tint_a}
    );
    return 1;
}

static int32 starry_new_world(lua_State* lua)
{
    StWorld* worldworld = StWorld_new();
    StWorld* world = lua_newuserdatauv(lua, sizeof(StWorld), 1);
    *world = *worldworld;
    StWorld_free(worldworld);
    return 1;
}

static int32 starry_world_set_current(lua_State* lua)
{
    StWorld* world = lua_touserdata(lua, 1);
    StWorld_set_current(world);
    return 1;
}

static int32 starry_world_get_current(lua_State* lua)
{
    StWorld* world = StWorld_current();
    lua_pushlightuserdata(lua, world);
    return 1;
}

static int32 starry_new_tile(lua_State* lua)
{
    StWorld* world = lua_touserdata(lua, 1);
    float64 x = luaL_checknumber(lua, 2);
    float64 y = luaL_checknumber(lua, 3);
    float64 z = luaL_checknumber(lua, 4);
    bool ground = lua_toboolean(lua, 5);
    const char* side0 = luaL_checkstring(lua, 6);
    const char* side1 = luaL_checkstring(lua, 7);
    const char* side2 = luaL_checkstring(lua, 8);
    const char* side3 = luaL_checkstring(lua, 9);

    StTile* tile = StWorld_new_tile(world, (stvec3){x, y, z}, ground, side0, side1, side2, side3);
    StTexture* texture0 = StTexture_new(side0);
    StTexture* texture1 = StTexture_new(side1);
    StTexture* texture2 = StTexture_new(side2);
    StTexture* texture3 = StTexture_new(side3);

    StTile* tilelua = lua_newuserdatauv(lua, sizeof(StTile), 1);
    *tilelua = *tile;
    return 1;
}

static int32 starry_get_tile(lua_State* lua)
{
    StWorld* world = lua_touserdata(lua, 1);
    float64 x = luaL_checknumber(lua, 2);
    float64 y = luaL_checknumber(lua, 3);
    float64 z = luaL_checknumber(lua, 4);
    bool ground = lua_toboolean(lua, 5);

    StTile* tile = StWorld_get_tile(world, (stvec3){x, y, z}, ground);
    StTile* tilelua = lua_newuserdatauv(lua, sizeof(StTile), 1);
    *tilelua = *tile;
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

    lua_pushcfunction(lua, starry_load_texture);
    lua_setfield(lua, -2, "starry_load_texture");

    lua_pushcfunction(lua, starry_draw_texture);
    lua_setfield(lua, -2, "starry_draw_texture");

    lua_pushcfunction(lua, starry_draw_texture_ext);
    lua_setfield(lua, -2, "starry_draw_texture_ext");

    lua_pushcfunction(lua, starry_new_world);
    lua_setfield(lua, -2, "starry_new_world");

    lua_pushcfunction(lua, starry_world_get_current);
    lua_setfield(lua, -2, "starry_world_get_current");

    lua_pushcfunction(lua, starry_world_set_current);
    lua_setfield(lua, -2, "starry_world_set_current");

    // global functions are accessed through the starry table
    lua_setglobal(lua, "starry");
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