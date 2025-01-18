# Lua_Cpp
an example show how to interact with c++ and lua



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
