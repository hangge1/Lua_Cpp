#include <iostream>

extern "C"
{
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
}

int CTest(lua_State* L)
{
    const char* first_param = lua_tostring(L, 1); //获取第一个参数, 字符串类型
    printf("first param is %s\n", first_param);

    int second_param = lua_tonumber(L, 2); //获取第二个参数, Number类型
    printf("second param is %d\n", second_param);

    bool third_param = lua_toboolean(L, 3); //获取第三个参数, boolean类型
    printf("third param is %s\n", third_param ? "true" : "false");

    return 0; //表示0个返回值
}

int main()
{
    lua_State* L = luaL_newstate();
    luaopen_base(L);

    lua_register(L, "CTest", CTest);

    if(luaL_loadfile(L, "first.lua") != 0)
    {
        const char* error = lua_tostring(L, -1);
        printf("lua load error: %s ",error);
        lua_close(L);
        return -1;
    }

    if(lua_pcall(L, 0, 0, 0) != 0)
    {
        const char* error = lua_tostring(L, -1);
        printf("lua call error: %s ",error);
        lua_close(L);
        return -2;
    }

    getchar();
    lua_close(L);

    return 0;
}