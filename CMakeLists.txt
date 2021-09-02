cmake_minimum_required(VERSION 3.17)
project(systheme)

set(CMAKE_CXX_STANDARD 20)

include_directories("include")

set(SOURCES
    src/opts.cpp src/opts.h
    src/user.cpp src/user.h
    src/engine.cpp src/engine.h
    src/lineparser.cpp src/lineparser.h
    src/symbols.cpp src/symbols.h
    src/symbolnode.cpp src/symbolnode.h
)

add_executable(${PROJECT_NAME} src/systheme.cpp ${SOURCES})
add_executable(TEST tests/tests.cpp ${SOURCES})
