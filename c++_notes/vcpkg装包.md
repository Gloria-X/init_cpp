CMakePresets.json

```json
{
    "version": 2,
    "configurePresets": [
      {
        "name": "vcpkg",
        "generator": "MinGW Makefiles",
        "binaryDir": "${sourceDir}/build",
        "cacheVariables": {
          "CMAKE_TOOLCHAIN_FILE": "$env{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
        }
      }
    ]
  }
```



CMakeUserPresets.json

```json
{
    "version": 2,
    "configurePresets": [
      {
        "name": "default",
        "inherits": "vcpkg",
        "environment": {
          "VCPKG_ROOT": "C:/Software/vcpkg"
        }
      }
    ]
  }
```





确认安装 [Visual Studio Build Tools](https://visualstudio.microsoft.com/visual-cpp-build-tools/) 并确保安装了 C++ 构建工具



setting.json

```bash
"C_Cpp.default.compilerPath": "C:\\Program Files (x86)\\Microsoft Visual Studio\\2022\\BuildTools\\VC\\Tools\\MSVC\\14.42.34433\\bin\\Hostx64\\x64\\cl.exe"

```



配置环境变量

手动运行

```bash
C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvarsall.bat
```


进到 Softeware/vcpkg 文件夹中
```bash
 ./vcpkg install libssh2
```



CMakeLists.txt 中手动添加 
```txt
include_directories(C:/Software/vcpkg/installed/x64-windows/include) # 手动添加 libssh2 头文件的路径

set(CMAKE_TOOLCHAIN_FILE "C:/Software/vcpkg/scripts/buildsystems/vcpkg.cmake") # 包含 vcpkg 的路径, VSCode 和 CMake 会自动配置好 libssh2 库路径
```