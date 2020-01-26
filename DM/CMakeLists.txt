cmake_minimum_required(VERSION 3.15)
project(DM C)

set(CMAKE_C_STANDARD 11)

add_executable(memory-allocator memory_alloc.h memory_alloc.c)

add_executable(tests tests.c)
target_link_libraries(tests cmocka)
