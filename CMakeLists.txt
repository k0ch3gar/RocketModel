cmake_minimum_required(VERSION 3.29)
project(RocketModel)

set(CMAKE_CXX_STANDARD 26)

add_executable(RocketModel main.cpp)

add_subdirectory(src)
add_subdirectory(lib)

target_include_directories( RocketModel
        PRIVATE .
)
