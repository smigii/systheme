cmake_minimum_required(VERSION 3.17)
project(systheme)

set(CMAKE_CXX_STANDARD 20)

include_directories("include")

add_executable(systheme src/main.cpp src/driver/Driver.cpp src/driver/Driver.h src/gui/WindowObj.cpp src/gui/WindowObj.h src/gui/WindowPane.cpp src/gui/WindowPane.h)

target_link_libraries(systheme ncurses)