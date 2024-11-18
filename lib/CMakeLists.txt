

target_include_directories( RocketModel
        PRIVATE raylib/include
)

target_link_directories( RocketModel
        PRIVATE raylib/lib
)

target_link_libraries( RocketModel
        PRIVATE libraylib.a
        PRIVATE raylib.a
        PRIVATE Winmm
)

target_include_directories( model
        PRIVATE raylib/include
)

target_link_directories( model
        PRIVATE raylib/lib
)

target_link_libraries( model
        PRIVATE libraylib.a
        PRIVATE raylib.a
        PRIVATE Winmm
)
