cmake_minimum_required(VERSION 3.10)   # 指定cmake最小版本
project(init_cpp)                     # 指定项目名称
include_directories(init_cpp include) # 指定头文件目录
include_directories(C:/Software/vcpkg/installed/x64-windows/include) # 手动添加 libssh2 头文件的路径
aux_source_directory(init_cpp src)    # 指定源文件目录

# file(GLOB ...)
file(GLOB_RECURSE SRC_FILES "src/*.cpp" "src/**/*.cpp")
add_executable(init_cpp ${SRC_FILES})
# add_executable(init_cpp src/main.cpp src/baseService/Log.cpp) # 指定程序入口

set(CMAKE_TOOLCHAIN_FILE "C:/Software/vcpkg/scripts/buildsystems/vcpkg.cmake") # 包含 vcpkg 的路径, VSCode 和 CMake 会自动配置好 libssh2 库路径

# 链接 libssh2 和 Winsock 库
target_link_libraries(init_cpp
    PRIVATE
    C:/Software/vcpkg/installed/x64-windows/lib/libssh2.lib
    ws2_32
)

