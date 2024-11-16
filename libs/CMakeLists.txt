cmake_minimum_required(VERSION 3.29)

target_include_directories( ${PROJECT_NAME}
        PRIVATE raylib/include/
)

target_link_directories( ${PROJECT_NAME}
        PRIVATE raylib/lib/
)

target_link_libraries( ${PROJECT_NAME}
        PRIVATE libraylib.a
        PRIVATE raylib.a
        PRIVATE Winmm
)