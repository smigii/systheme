cmake_minimum_required(VERSION 3.17)
project(systheme)

set(CMAKE_CXX_STANDARD 20)

include_directories("include")

set(SOURCES
        src/utils/opts.cpp src/utils/opts.h
        src/utils/user.cpp src/utils/user.h
        src/interface.cpp src/interface.h
        src/symbolmap.cpp src/symbolmap.h
        src/symbolnode.cpp src/symbolnode.h
        src/templateparser.cpp src/templateparser.h
        src/templateheader.cpp src/templateheader.h
        src/utils/tokenizer.cpp src/utils/tokenizer.h
        src/utils/verbosityhandler.cpp src/utils/verbosityhandler.h)

add_executable(${PROJECT_NAME} src/main.cpp ${SOURCES})
add_executable(TEST tests/tests.cpp ${SOURCES})
