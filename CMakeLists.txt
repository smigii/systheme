cmake_minimum_required(VERSION 3.17)
project(systheme)

set(CMAKE_CXX_STANDARD 20)

include_directories("include")

add_executable(systheme src/main.cpp src/driver/Driver.cpp src/driver/Driver.h)

target_link_libraries(systheme ncurses)