cmake_minimum_required(VERSION 3.15)
project(TP8_Syscalls C)

set(CMAKE_C_STANDARD 11)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
add_compile_options(-g -O0 -Wall -Wextra -Wold-style-cast -Wdouble-promotion
                    -Wshadow -Wformat=2 -Wunreachable-code-aggressive)


add_executable(proc-sync proc-sync.c)

add_executable(sem sem.c)
target_link_libraries(sem Threads::Threads)

add_executable(bank bank.c)
add_executable(bank-init-sem bank-init-sem.c)
target_link_libraries(bank Threads::Threads)
target_link_libraries(bank-init-sem Threads::Threads)
