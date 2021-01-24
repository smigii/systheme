cmake_minimum_required(VERSION 3.17)
project(systheme)

set(CMAKE_CXX_STANDARD 20)

include_directories("include")

add_executable(systheme
        src/main.cpp
        src/gui/WObj.cpp src/gui/WObj.h src/gui/WPane.cpp src/gui/WPane.h src/gui/WPage.cpp src/gui/WPage.h src/gui/ui.h
        src/driver/Driver.cpp src/driver/Driver.h
        src/tpc/Theme.cpp src/tpc/Theme.h src/tpc/Config.cpp src/tpc/Config.h src/tpc/Program.cpp src/tpc/Program.h src/helper/vec_sort.h src/gui/Ui.cpp src/gui/Ui.h src/gui/Page.cpp src/gui/Page.h src/gui/Menu.cpp src/gui/Menu.h)

target_link_libraries(systheme panel)
target_link_libraries(systheme menu)
target_link_libraries(systheme ncurses)