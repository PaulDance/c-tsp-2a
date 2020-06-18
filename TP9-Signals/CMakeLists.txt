cmake_minimum_required(VERSION 3.16)
project(TP9_Signals C)

set(CMAKE_C_STANDARD 11)
add_compile_options(-g -O3 -Wall -Wextra -Wold-style-cast -Wdouble-promotion
                    -Wshadow -Wformat=2 -Wunreachable-code-aggressive)

add_executable(sig sig.c)
add_executable(test_map map/test_map.c map/map.c)
add_executable(test_map_tree map/test_map.c map/map_tree.c)
