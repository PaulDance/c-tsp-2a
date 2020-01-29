cmake_minimum_required(VERSION 3.15)
project(TP4_Pointers C)

set(CMAKE_C_STANDARD 11)
add_compile_options(-O0 -Wall -Wextra -Wold-style-cast -Wdouble-promotion
					-Wshadow -Wformat=2 -Wunreachable-code-aggressive)

add_executable(ex1-first-pointers ex1-first-pointers.c)
add_executable(ex2-arrays-pointers ex2-arrays-pointers.c)
