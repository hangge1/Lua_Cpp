// 01_LuaCpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

extern "C"
{
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
}

int main()
{
    lua_State* L = luaL_newstate();
    luaopen_base(L);
    luaL_loadfile(L, "first.lua");
    lua_pcall(L, 0, 0, 0);

    return 0;
}