cmake_minimum_required(VERSION 3.15)
project(TP5_Files C)

set(CMAKE_C_STANDARD 11)
add_compile_options(-g -O0 -Wall -Wextra -Wold-style-cast -Wdouble-promotion
                    -Wshadow -Wformat=2 -Wunreachable-code-aggressive)

add_executable(cat-bank-file cat-bank-file.c)
add_executable(xor xor.c)
add_executable(generate generate.c)
add_executable(modify modify.c)
