cmake_minimum_required(VERSION 3.15)   # 指定cmake最小版本
project(init_cpp)                     # 指定项目名称
include_directories(init_cpp include) # 指定头文件目录
aux_source_directory(init_cpp src)    # 指定源文件目录

# file(GLOB ...)
file(GLOB_RECURSE SRC_FILES "src/*.cpp" "src/**/*.cpp")
add_executable(init_cpp ${SRC_FILES})
# add_executable(init_cpp src/main.cpp src/baseService/Log.cpp) # 指定程序入口
