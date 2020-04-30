cmake_minimum_required(VERSION 3.15)
project(TP1_First_Steps C)

set(CMAKE_C_STANDARD 11)
add_compile_options(-g -O0 -Wall -Wextra -Wold-style-cast -Wdouble-promotion
                    -Wshadow -Wformat=2 -Wunreachable-code-aggressive)

add_executable(ex1-hello-world ex1-hello-world.c)
add_executable(ex2-is-prime ex2-is-prime.c)
add_executable(ex3-price-is-right ex3-price-is-right.c)
add_executable(ex4-exp ex4-exp.c)
add_executable(ex5-bin ex5-bin.c)
