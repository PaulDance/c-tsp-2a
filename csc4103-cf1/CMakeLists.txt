cmake_minimum_required(VERSION 3.16)
project(CF1 C)

set(CMAKE_C_STANDARD 11)
add_compile_options(-g -O3 -Wall -Wextra -Wold-style-cast -Wdouble-promotion
                    -Wshadow -Wformat=2 -Wunreachable-code-aggressive)

add_executable(exo1 exo1.c)
add_executable(exo2 exo2.c)
add_executable(exo3 exo3.c)
add_executable(exo4 exo4.c)
