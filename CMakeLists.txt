cmake_minimum_required(VERSION 3.13)
project(zalloc C)

set(CMAKE_C_STANDARD 11)

add_library(${PROJECT_NAME} SHARED)

target_sources(
    ${PROJECT_NAME}
    PRIVATE
        src/zalloc.c
        src/internal/zmem_header.h
        src/internal/zmem_header.c
        src/internal/helpers.h
        src/internal/helpers.c
    PUBLIC
        src/include/zalloc.h
)

target_include_directories(${PROJECT_NAME} PRIVATE src/include)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)