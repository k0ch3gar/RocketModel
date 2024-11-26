include(FetchContent)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
)

FetchContent_MakeAvailable(raylib)

target_link_libraries( RocketModel
        PRIVATE raylib
        PRIVATE Winmm
)

target_link_libraries( model
        PRIVATE raylib
        PRIVATE Winmm
)
