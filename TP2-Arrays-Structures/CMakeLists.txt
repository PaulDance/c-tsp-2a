cmake_minimum_required(VERSION 3.15)
project(TP2_Arrays_Structures C)

set(CMAKE_C_STANDARD 11)

add_executable(TP2_Arrays_Structures main.c sort.c sort.h grid.c grid.h plot.c plot.h)
target_link_libraries(TP2_Arrays_Structures m)
