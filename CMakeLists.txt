set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

cmake_minimum_required(VERSION 3.18)

project(main)

add_executable(main
    src/main.c
    src/piecetable.c
)

target_compile_options(main
    PRIVATE
    -std=c2x
    -Werror=vla
)
