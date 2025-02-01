#### 删除 CMake 缓存文件

build 目录中 CMakeCache.txt 和 CMakeFiles 目录

#### 选择生成器

ctrl + shift +P --> 输入 CMake: Select a Kit --> 选择 gcc minGW

#### 重新匹配 CMake

```bash
cd build

cmake -G "MinGW Makefiles" ..
```

#### 尝试构建项目

```bash
cmake --build .
```



 