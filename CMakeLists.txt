cmake_minimum_required(VERSION 3.17)
project(systheme)

set(CMAKE_CXX_STANDARD 20)

include_directories("include")

add_executable(systheme src/systheme.cpp src/classes.cpp)

add_executable(test_user src/tests.cpp src/classes.cpp)