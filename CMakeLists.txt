cmake_minimum_required(VERSION 3.29)
project(RocketModel)

set(CMAKE_CXX_STANDARD 26)

add_executable(RocketModel main.cpp)

add_subdirectory(libs src)

target_include_directories(${PROJECT_NAME}
        PRIVATE .
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE gpdrawer
)

