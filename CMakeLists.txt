cmake_minimum_required(VERSION 4.1)
project(Casino)

set(CMAKE_CXX_STANDARD 20)

add_executable(Casino
        main.cpp
        Game.h
        Game.cpp
        Slots.h
        Slots.cpp
        main.cpp
        Player.h
        Player.cpp
)