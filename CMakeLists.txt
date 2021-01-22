cmake_minimum_required(VERSION 3.17)
project(systheme)

set(CMAKE_CXX_STANDARD 20)

include_directories("include")

add_executable(systheme
        src/main.cpp
        src/gui/WindowObj.cpp src/gui/WindowObj.h src/gui/WindowPane.cpp src/gui/WindowPane.h src/gui/WindowPage.cpp src/gui/WindowPage.h src/gui/ui.h
        src/driver/Driver.cpp src/driver/Driver.h
        src/tpc/Theme.cpp src/tpc/Theme.h src/tpc/Config.cpp src/tpc/Config.h src/tpc/Program.cpp src/tpc/Program.h)

target_link_libraries(systheme panel)
target_link_libraries(systheme menu)
target_link_libraries(systheme ncurses)