#include <iostream>

extern "C"
{
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
}

int CTest(lua_State* L)
{
    //1 获取数组长度
    //2 遍历数组元素
    lua_len(L, 1); //获取栈底的数据长度, 把它压栈
    int arrLen = lua_tointeger(L, -1);
    printf("array len = %d\n", arrLen);
    lua_pop(L, 1);

    for(int i = 1; i <= arrLen; i++)
    {
        lua_pushnumber(L, i); //压入访问下标
        lua_gettable(L, 1); //pop下标, 压入对应下标元素
        printf("arr[%d] = %s\n", i, lua_tostring(L, -1));
        lua_pop(L, 1); //弹出元素
    }

    return 0; //表示0个返回值
}

int Test_TableParam(lua_State* L)
{
    lua_pushnil(L); //nil作为第一个key,这是遍历规则

    //根据当前栈底判断key是否存在后续,有就弹出key,压入后一个元素的key和value
    while(lua_next(L, 1) != 0) 
    {
        printf("key = %s ", lua_tostring(L, -2));
        printf("value = %s \n", lua_tostring(L, -1));
        lua_pop(L, 1);
    }
    
    return 0;
}

int Test_GetField(lua_State* L)
{
    lua_getfield(L, 1, "name");
    printf("table[name] = %s ", lua_tostring(L, -1));
    lua_pop(L, 1);

    return 0;
}

int Test_CheckType(lua_State* L)
{
    luaL_checktype(L, 1, LUA_TTABLE);

    if(lua_type(L, 1) != LUA_TTABLE)
    {
        printf("type is not table!\n");
    }

    return 0;
}

int Test_ReturnNormalValue(lua_State* L)
{
    lua_pushnumber(L, 99); //第一个返回值
    lua_pushstring(L, "Hello World!"); //第二个返回值

    return 2; //返回2个值
}

int Test_ReturnTableValue(lua_State* L)
{
    lua_newtable(L);

    //插入第一对key,value
    lua_pushstring(L, "Name");
    lua_pushstring(L, "John");
    lua_settable(L, -3); //弹出{key, value}到-3指向的表

    //插入第二对key,value
    lua_pushstring(L, "Age");
    lua_pushnumber(L, 13);
    lua_settable(L, -3);

    return 1; //返回1个值
}

void Test_GetLuaVar(lua_State* L)
{
    lua_getglobal(L, "Width");
    int width = lua_tonumber(L, -1);
    lua_pop(L, 1);
    printf("width = %d\n", width);
}

void Test_SetLuaVar(lua_State* L)
{
    lua_pushstring(L, "Hello World Lua!");
    lua_setglobal(L, "TestVar"); //弹出栈顶, 设置全局变量名称为TestVar
}

void Test_GetLuaTable(lua_State* L)
{
    lua_getglobal(L, "conf"); //获取conf变量,压入栈顶
    lua_getfield(L, -1, "ip"); //获取key为ip的值,压入栈顶
    printf("ip = %s\n", lua_tostring(L, -1));
    lua_pop(L, 1); //出栈ip的值

    lua_getfield(L, -1, "port");
    printf("port = %d\n", lua_tointeger(L, -1));
    lua_pop(L, 2); //出栈port的值和conf变量
}

void Test_SetLuaTable(lua_State* L)
{
    lua_newtable(L);
    lua_pushstring(L, "min_thread_num");
    lua_pushnumber(L, 5);
    lua_settable(L, -3);

    lua_pushstring(L, "max_thread_num");
    lua_pushnumber(L, 10);
    lua_settable(L, -3);

    lua_setglobal(L, "thread_conf");
}


int main()
{
    lua_State* L = luaL_newstate();
    luaopen_base(L);

    lua_register(L, "CTest", CTest);
    lua_register(L, "Test_TableParam", Test_TableParam);
    lua_register(L, "Test_GetField", Test_GetField);
    lua_register(L, "Test_CheckType", Test_CheckType);
    lua_register(L, "Test_ReturnNormalValue", Test_ReturnNormalValue);
    lua_register(L, "Test_ReturnTableValue", Test_ReturnTableValue);
    
    Test_SetLuaVar(L);
    Test_SetLuaTable(L);

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

    
    //Test_GetLuaVar(L);
    //Test_GetLuaTable(L);

    getchar();
    lua_close(L);

    return 0;
}