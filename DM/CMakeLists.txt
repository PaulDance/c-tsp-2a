cmake_minimum_required(VERSION 3.15)
project(DM C)

set(CMAKE_C_STANDARD 11)
add_compile_options(-O2 -Wall -Wextra -Wold-style-cast -Wdouble-promotion
					-Wshadow -Wformat=2 -Wunreachable-code-aggressive)

add_library(memory-allocator memory_alloc.h memory_alloc.c)

add_executable(tests tests.c)
target_link_libraries(tests cmocka)
