# Lua_Cpp
an example show how to interact with c++ and lua



### 源码编译Lua

**1 编译lua为动态库**

源码来源于目录下:  lua-5.4.7.tar.gz

(1) 创建C++ DLL项目

所有lua源代码加入工程,  需要修改一下lua.c中的main,  改个名字,不然冲突

(2) 修改Output Directory

```
$(SolutionDir)..\bin\$(Platform)\$(Configuration)\
```

(3) 添加宏 LUA_BUILD_AS_DLL,  表明编译lua以动态库导出

(4) 修改导入库路径

```
$(SolutionDir)..\lib\$(Platform)\$(Configuration)\
```



**2 添加C++测试库**

(1) 修改输出目录, 为了和DLL同目录

```
$(SolutionDir)..\bin\$(Platform)\$(Configuration)\
```

(2) 添加头文件包含目录

(3) 添加库路径

(4) 添加链接库

(5) 添加测试代码

```c++
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
```

(6) 添加lua文件

```
print('Hello Lua!')
```

(7) 运行测试工程

![image-20250119001039323](README/image-20250119001039323.png)

























