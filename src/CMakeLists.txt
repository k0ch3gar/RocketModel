cmake_minimum_required(VERSION 3.29)

add_library(model
        STATIC GraphDrawer.cpp
        Rocket.cpp
        Rocket.h
        Window.cpp
        Window.h
        IDrawable.h
        Button.cpp
        Button.h
)

target_link_libraries( RocketModel
        PRIVATE model
)

target_include_directories( RocketModel
        PRIVATE .
)