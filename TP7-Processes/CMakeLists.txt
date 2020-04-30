cmake_minimum_required(VERSION 3.15)
project(TP7_Processes C)

set(CMAKE_C_STANDARD 11)
add_compile_options(-g -O0 -Wall -Wextra -Wold-style-cast -Wdouble-promotion
                    -Wshadow -Wformat=2 -Wunreachable-code-aggressive)

add_executable(fork-chain fork-chain.c)

add_executable(mysh mysh.c)
target_link_libraries(mysh readline linked-list)

add_library(linked-list SHARED linked-list.c)
set_target_properties(linked-list PROPERTIES PUBLIC_HEADER linked-list.h)
