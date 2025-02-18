#include <stdio.h>
#define LUA_IMPL
#include "minilua.h"
#include "extensions.h"

lua_State* lua;

void StExtensions_new()
{
    lua = luaL_newstate();
    if (lua == NULL) {
        fprintf(stderr, "[EXTENSIONS] Couldn't initialize Lua\n");
    }
    printf("[EXTENSIONS] Initialized Lua\n");
}

void StExtensions_free()
{
    lua_close(lua);
    printf("[EXTENSIONS] Lua is dead.\n");
}