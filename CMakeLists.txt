cmake_minimum_required(VERSION 3.17)
project(systheme)

set(CMAKE_CXX_STANDARD 20)

include_directories("include")

add_executable(
        systheme
        src/systheme.cpp
        src/opts.cpp src/opts.h
        src/user.cpp src/user.h
        src/engine.cpp src/engine.h
        src/lineparser.cpp src/lineparser.h
)
