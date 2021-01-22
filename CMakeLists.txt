cmake_minimum_required(VERSION 3.17)
project(systheme)

set(CMAKE_CXX_STANDARD 20)

include_directories("include")

add_executable(systheme src/main.cpp src/gui/WindowObj.cpp src/gui/WindowObj.h src/gui/WindowPane.cpp src/gui/WindowPane.h src/gui/WindowPage.cpp src/gui/WindowPage.h src/driver/Driver.cpp src/driver/Driver.h src/driver/Theme.cpp src/driver/Theme.h src/driver/Config.cpp src/driver/Config.h src/driver/Program.cpp src/driver/Program.h)

target_link_libraries(systheme panel)
target_link_libraries(systheme menu)
target_link_libraries(systheme ncurses)