cmake_minimum_required(VERSION 3.10)
project(minesweeper)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(minesweeper main.cpp board.cpp zones.cpp cell.cpp graph.cpp cellManager.cpp)
target_link_libraries(minesweeper sfml-graphics sfml-window sfml-system)

